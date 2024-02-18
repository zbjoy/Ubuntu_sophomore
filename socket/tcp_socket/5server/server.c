#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>

char buf[1500] = "";
int num = 0;

void* server_func(void* arg)
{
	while(1)
	{	
		int lfd = *(int*)arg;
		
	}
}

void* client_func(void* arg)
{
	while(1)
	{	
		int cfd = *(int*)arg;
		num = recv(cfd, buf, sizeof(buf), 0);	
		if(num <= 0)
		{
			printf("recv error.......\n");	
			return NULL;
		}
		printf("%s", buf);
		send(cfd, buf, num, 0);	
		memset(buf, 0, sizeof(buf));
		num = 0;
	}
}

int main(int argc, char** argv)
{
	if(argc != 3)	
	{
		printf("usage: ./a.out ip port\n");
		return 1;
	}

	short port = atoi(argv[2]);
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
	{
		perror("socket");	
		return 1;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr.s_addr);
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
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);

	pthread_t server_tid;
	pthread_t client_tid;

	//pthread_create(&server_tid, NULL, server_func, (void*)&lfd);

	while(1)
	{
		int cfd = accept(lfd, (struct sockaddr*)&client_addr, &client_addrlen);	
		pthread_create(&client_tid, NULL, client_func, (void*)&cfd);
	}

	pthread_join(server_tid, NULL);

	return 0;
}
