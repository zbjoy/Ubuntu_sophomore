#include "server.h"

int initListenFd(unsigned short port)
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
	{
		perror("socket");	
		return -1;
	}

	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.56.128", &addr.sin_addr.s_addr);

	int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == -1)
	{
		perror("bind");	
		return -1
	}

	ret = listen(lfd, 128);
	if(ret == -1)
	{
		perror("listen");	
		return -1;
	}

}

int epoll_run(unsigned short port)
{
	int lfd = initListenFd(port);	
	if(lfd == -1)
	{
		return -1;	
	}
	int efd = epoll_create(10);

	struct epoll_event ev, evs[1024];
	ev.events = EPOLLIN;
	ev.data.fd = lfd;
	epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ev);

	int maxEvents = sizeof(evs) / sizeof(evs[0]);

	while(1)
	{

		int num = epoll_wait(efd, evs, maxEvents, -1);	
		for(int i = 0; i < num; ++i)
		{
			int curfd = evs[i].data.fd;
			unsigned int events = evs[i].events;
			if(curfd == lfd && events == EPOLLIN)	
			{
					
			}
		}
		
	}
}
