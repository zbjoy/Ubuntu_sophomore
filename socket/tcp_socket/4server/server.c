#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd == -1)
	{
		perror("socket");	
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	inet_pton(AF_INET, "192.168.56.128", &addr.sin_addr.s_addr);
	socklen_t addrlen = (socklen_t)sizeof(addr);
	int ret = bind(sock_fd, (struct sockaddr*)&addr, addrlen);
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

	int fd = accept(sock_fd, (struct sockaddr*)&addr, &addrlen);
	printf("连接成功.....\n");
	while(1)
	{
		printf("you can get client information......\n");
		char buf[1024] = "";
		int n = read(fd, buf, sizeof(buf));	
		if(n == 0)
		{
			printf("no read.....\n");		
		}
		printf("read.....\n");
		write(STDOUT_FILENO, buf, n);
		printf("write stdout......\n");
	//	n = read(STDIN_FILENO, buf, sizeof(buf));
		char hello[] = "i listen to you.....\n";
		int num = read(STDIN_FILENO, buf, sizeof(buf));
		write(fd, buf, num);
		//write(sock_fd, hello, sizeof(hello));
	}

	close(fd);
	close(sock_fd);

	return 0;
}
