#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("usage: ./a.out ip port\n");	
		return -1;
	}
	unsigned short port = atoi(argv[2]);
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
	{
		perror("socket");	
		return -1;
	}


	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr.s_addr);
	int ret = bind(lfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind");	
		return -1;
	}

	ret = listen(lfd, 128);
	if(ret == -1)
	{
		perror("listen");	
		return -1;
	}

	int efd = epoll_create(1);
	if(efd == -1)
	{
		perror("epoll_create");	
		return -1;
	}

	struct epoll_event ev, evs[1024];
	ev.events = EPOLLIN;
	ev.data.fd = lfd;
	epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ev);

	while(1)
	{
		int num = epoll_wait(efd, evs, 1024, -1);	
		for(int i = 0; i < num; i++)
		{
			if(evs[i].data.fd == lfd && evs[i].events == EPOLLIN)	
			{
				struct sockaddr_in client_addr;
				socklen_t client_addrlen = sizeof(client_addr);
				int cfd = accept(evs[i].data.fd, (struct sockaddr*)&client_addr, &client_addrlen);
				struct epoll_event tempev;
				tempev.data.fd = cfd;
				tempev.events = EPOLLIN;
				epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &tempev);

				char ip[16] = "";
				printf("the ip is %s port is %d connect .......\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip, sizeof(ip)), ntohs(client_addr.sin_port));
			}
			else if(evs[i].events == EPOLLIN)
			{
				char buf[1500] = "";
				int nums = recv(evs[i].data.fd, buf, sizeof(buf), 0);	
				if(nums <= 0)
				{
					perror("close");	
					epoll_ctl(efd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
					close(evs[i].data.fd);
					continue;
				}
				send(evs[i].data.fd, buf, nums, 0);
				printf("%s", buf);
			}
		}

	}

	close(lfd);
	close(efd);	

	return 0;
}
