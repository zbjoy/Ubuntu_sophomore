#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

void* readserver(void* arg)
{

	char buf[1024] = "";
	int sock_fd = *(int*)arg;
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		int n = read(sock_fd, buf, sizeof(buf));	
		if(n == 0)
		{
			printf("server close......\n");
			return NULL;
		}
		else if(n < 0)
		{	
			perror("read");	
			return NULL;
		}

		write(STDOUT_FILENO, buf, n);
			
	}
}

void* writeserver(void* arg)
{

	char buf[1024] = "";
	int sock_fd = *(int*)arg;
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		int n = read(STDIN_FILENO, buf, sizeof(buf));	
		if(n <= 0)
		{	
			perror("read from stdin error......\n");	
			return NULL;
		}

		write(sock_fd, buf, n);
			
	}
}


int main(void)
{
	pthread_t tidread;
	pthread_t tidwrite;

	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd == -1)
	{
		perror("socket");	
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	//addr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "192.168.56.128", &addr.sin_addr.s_addr);

	int ret = connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == -1)
	{
		perror("connect");	
		return 1;
	}

	pthread_create(&tidread, NULL, readserver, (void*)&sock_fd);
	pthread_create(&tidwrite, NULL, writeserver, (void*)&sock_fd);

	pthread_join(tidread, NULL);
	pthread_join(tidwrite, NULL);
	close(sock_fd);
	return 0;
}
