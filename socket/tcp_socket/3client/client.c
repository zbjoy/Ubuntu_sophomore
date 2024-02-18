#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("socket");	
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	inet_pton(AF_INET, "192.168.56.128", &addr.sin_addr.s_addr);

	socklen_t addrlen = (socklen_t)sizeof(addr);
	int ret = connect(socket_fd, (struct sockaddr*)&addr, addrlen);
	if(ret == -1)
	{
		perror("connect");	
		return 1;
	}

	char buf[1024];
	while(1)
	{
		int n = read(STDIN_FILENO, buf, sizeof(buf));	
		write(socket_fd, buf, n);
		n = read(socket_fd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, n);
	}

	close(socket_fd);

	return 0;
}
