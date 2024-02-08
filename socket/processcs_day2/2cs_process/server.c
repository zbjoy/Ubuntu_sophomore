#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "wrap.h"

void free_process(int sig)
{
	pid_t pid;
	while(1)
	{
		pid = waitpid(-1, NULL, WNOHANG);	
		if(pid <= 0)
		{
			break;	
		}
		else
		{
			printf("child pid = %d ......\n", pid);	
		}
	}
}

int main(void)
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL);

	//创建套接字
	int sock_fd = tcp4bind(8080, NULL);

	Listen(sock_fd, 128);

	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);

	while(1)
	{
		char ip[16];
		
		int client_fd = Accept(sock_fd, (struct sockaddr*)&addr, &addrlen);	
		printf("new client ip = %s  port = %d......\n", inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, 16), ntohs(addr.sin_port));

		pid_t pid;
		pid = fork();
		if(pid < 0)
		{
			perror("fork");	
			exit(0);
		}
		else if(pid == 0)
		{
			close(sock_fd);	
			char buf[512] = "";
			int theIp[16];
			while(1)
			{
				memset(buf, 0, sizeof(buf));
				
				int n = read(client_fd, buf, sizeof(buf));	
				if(n < 0)
				{
					perror("");	
					close(client_fd);
					exit(0);
				}
				else if(n == 0)
				{
					printf("client ip is %s, port is %d    close......\n", inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, 16), ntohs(addr.sin_port));	
					close(client_fd);
					exit(0);
				}
				else
				{
					char temp[1024] = "";
					int num = sprintf(temp, "you say: %s \n", buf);	
					write(client_fd, buf, num);
				}
			}	
		}
		else
		{
			close(client_fd);	

			struct sigaction act;
			act.sa_flags = 0;
			act.sa_handler = free_process;
			sigprocmask(SIG_UNBLOCK, &set, NULL);
		}
	}

	return 0;
}
