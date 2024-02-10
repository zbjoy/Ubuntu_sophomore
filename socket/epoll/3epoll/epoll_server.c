#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("usage ./a.out ip port\n");	
		return 1;
	}

	short port = atoi(argv[2]);

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == -1)
	{
		perror("server_fd");	
		return 1;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = ntohs(port);
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr.s_addr);
	int ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind");	
		return 1;
	}

	ret = listen(server_fd, 128);
	if(ret == -1)
	{
		perror("listen");	
		return 1;
	}

	int epfd;
	epfd = epoll_create(1);
	if(epfd == -1)
	{
		perror("epoll_create");	
		return 1;
	}

	struct epoll_event ev, evs[1024];
	ev.data.fd = server_fd;
	ev.events = EPOLLIN;

	epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

	while(1)
	{
		memset(evs, 0, sizeof(evs));
		ret  = epoll_wait(epfd, evs, 1024, -1);	
		if(ret <= 0)
		{
			perror("epoll_wait");	
			return 1;
		}
		
		for(int i = 0; i < ret; i++)	
		{
			if(evs[i].data.fd == server_fd && evs[i].events & EPOLLIN)	
			{
				struct sockaddr_in client_addr;
				socklen_t client_addr_len = sizeof(client_addr);
				int temp_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);	
				char ip[16] = "";
				printf("a client ip is %s  port is %d  connect.......\n",
						inet_ntop(AF_INET, (struct sockaddr*)&client_addr.sin_addr.s_addr, ip, 16),
						htons(client_addr.sin_port));
				struct epoll_event tempev;
				tempev.data.fd = temp_fd;
				tempev.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_ADD, temp_fd, &tempev);
			}
			else if(evs[i].data.fd != -1 && evs[i].events & EPOLLIN)
			{
				char buf[1500] = "";
				int num = read(evs[i].data.fd, buf, sizeof(buf));		
				if(num <= 0)
				{
					struct epoll_event tempev;
					printf("a client close.......\n");	
					close(evs[i].data.fd);
					epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &tempev);
					continue;
				}

				write(evs[i].data.fd, buf, num);
				printf("the client say: %s\n", buf);
			}
		}
	}

	close(server_fd);
	return 0;
}
