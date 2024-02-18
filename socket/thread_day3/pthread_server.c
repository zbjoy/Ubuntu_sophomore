#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>
#include "wrap.h"

typedef struct info
{
	int client_fd;
	struct sockaddr_in addr;
}CINFO;

void* client_fun(void* arg);

int main(int argc, char** argv)
{
	if(argc != 2)	
	{
		printf("usage: a.out port\n");	
		return 1;
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	short port = atoi(argv[1]);
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd == -1)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	int ret = inet_pton(AF_INET, "192.168.56.128", &addr.sin_addr.s_addr);
	if(ret <= 0)
	{
		perror("inet_pton");	
		return 1;
	}
	ret = bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == -1)
	{
		perror("bind");	
		return 1;
	}
	ret = listen(sock_fd, 128);
	if(ret == -1)
	{
		perror("listen");	
		return 1;
	}

	struct sockaddr_in clientaddr;
	int client_fd;
	socklen_t clientlen = sizeof(clientaddr);
	CINFO* info;
	while(1)
	{
		client_fd = accept(sock_fd, (struct sockaddr*)&clientaddr, &clientlen);	
		if(client_fd == -1)
		{
			perror("accept");	
			return 1;
		}

		info = malloc(sizeof(CINFO));
		info->client_fd = client_fd;
		info->addr = clientaddr;

		pthread_t tid;
		pthread_create(&tid, &attr, client_fun, info);
	}

	return 0;
}

void* client_fun(void* arg)
{
	CINFO* info = (CINFO*)arg;
	char ip[16] = "";

	printf("new pthread the client ip is %s   port is %d ......\n", inet_ntop(AF_INET, (struct sockaddr*)&info->addr.sin_addr.s_addr, ip, 16), ntohs(info->addr.sin_port));

	while(1)
	{
		char buf[1024] = "";
		int count = 0;
		count = read(info->client_fd, buf, sizeof(buf));	
		if(count < 0)
		{
			perror("read");	
			break;
		}
		else if(count == 0)
		{
			printf("the ip is %s  port is %d client close......\n", inet_ntop(AF_INET, (struct sockaddr*)&info->addr.sin_addr.s_addr, ip, 16), ntohs(info->addr.sin_port));	
			break;
		}
		else
		{
			printf("%s\n", buf);	
			write(info->client_fd, buf, count);
		}
	}

	sleep(1);
	close(info->client_fd);
	free(info);

}
