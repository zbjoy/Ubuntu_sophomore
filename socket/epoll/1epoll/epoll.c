#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("usage: ./a.out ip port\n");	
		return 1;
	}
	short port = atoi(argv[2]);
	int efd = epoll_create(10);
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
	{
		perror("socket");	
		return 1;
	}

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_pton(AF_INET, argv[1], &serveraddr.sin_addr.s_addr);

	int ret = bind(lfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(ret == -1)
	{
		perror("bind");	
		return 1;
	}
	ret = listen(lfd, 128);
	if(ret == -1)
	{
		perror("listen");	
		return 1;
	}

	struct epoll_event ev;
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ev);

	struct epoll_event allev[1024];

	while(1)
	{
		memset(allev, 0, sizeof(allev));
		ret = epoll_wait(efd, allev, 1024, -1);	
		printf("ret is %d\n", ret);
		if(ret == -1)
		{
			perror("epoll_wait");	
			return 1;
		}

		//if(allev[0].data.fd != -1 && allev[0].events & EPOLLIN)
		//{
			//printf("allev[0].data.fd is %d ......\n", allev[0].data.fd);
			//if(allev[0].events & EPOLLIN)	
			//{
				//struct epoll_event tempev;
				//memset(&tempev, 0, sizeof(tempev));

				//struct sockaddr_in tempaddr;
				//memset(&tempaddr, 0, sizeof(tempaddr));
				//socklen_t templen = sizeof(tempaddr);
				//tempev.data.fd = accept(lfd, (struct sockaddr*)&tempaddr, &templen);
				//printf("accept ret is %d\n", tempev.data.fd);
				//if(tempev.data.fd == -1)
				//{
					//perror("accept");	
					//return 1;
				//}
				//printf("a client connect ......\n");
				//tempev.events = EPOLLIN;
				//epoll_ctl(efd, EPOLL_CTL_ADD, tempev.data.fd, &tempev);	
			//}
		//}
		int i = 0;
		
		for(i = 0; i < ret; i++)	
		{
			printf("allev[i].data.fd is %d ......\n", allev[i].data.fd);
			if(allev[i].events & EPOLLIN)
			{
				if(allev[i].data.fd == lfd)
				{
				
					struct epoll_event tempev;
					memset(&tempev, 0, sizeof(tempev));

					struct sockaddr_in tempaddr;
					memset(&tempaddr, 0, sizeof(tempaddr));
					socklen_t templen = sizeof(tempaddr);
					tempev.data.fd = accept(lfd, (struct sockaddr*)&tempaddr, &templen);
					printf("accept ret is %d\n", tempev.data.fd);
					if(tempev.data.fd == -1)
					{
						perror("accept");	
						return 1;
					}
					printf("a client connect ......\n");
					tempev.events = EPOLLIN;
					epoll_ctl(efd, EPOLL_CTL_ADD, tempev.data.fd, &tempev);	
				}
				else
				{
				
					char buf[1024] = "";
					int num = read(allev[i].data.fd, buf, sizeof(buf));
					if(num <= 0)
					{
						perror("read");	
						close(allev[i].data.fd);
						printf("a client close......\n");
						//i++;
						continue;
					}
					write(allev[i].data.fd, buf, num);	
					printf("%s", buf);
					fflush(stdout);
					//i++;	
				}
			}
			else
			{
				//i++;	
			}
		}
		
	}

	return 0;
}
