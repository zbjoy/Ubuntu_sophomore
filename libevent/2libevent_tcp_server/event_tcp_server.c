#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <event.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void cfd_func(int cfd, short events, void* arg)
{
	char buf[1500] = "";
	int n = recv(cfd, buf, sizeof(buf), 0);
	if(n <= 0)
	{
		perror("recv close or faile");	
		return;
	}

	printf("%s", buf);
	send(cfd, buf, n, 0);
}

void lfd_func(int lfd, short events, void* arg)
{
	struct event_base* base = (struct event_base*)arg;
	int cfd = accept(lfd, NULL, NULL);
	if(cfd == -1)
	{
		perror("accept");	
		return;
	}

	struct event* ev = event_new(base, cfd, EV_READ | EV_PERSIST, cfd_func, NULL);
	event_add(ev, NULL);
}	

int main(void)
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
	{
		perror("socket");	
		return 1;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	inet_pton(AF_INET, "192.168.56.128", &server_addr.sin_addr.s_addr);
	int ret = bind(lfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
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

	struct event_base* base = event_base_new();
	if(base == NULL)
	{
		printf("event_base_new failed.......\n");	
		return 1;
	}

	struct event* ev = event_new(base, lfd, EV_READ | EV_PERSIST, lfd_func, base);
	if(ev == NULL)
	{
		printf("event_new failed .......\n");	
		return 1;
	}

	ret = event_add(ev, NULL);
	if(ret == -1)
	{
		printf("event_add failed.......\n");	
		return 1;
	}

	event_base_dispatch(base);

	close(lfd);
	event_base_free(base);


	return 0;
}
