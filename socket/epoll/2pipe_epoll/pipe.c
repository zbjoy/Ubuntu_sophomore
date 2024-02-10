#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>

int main(void)
{
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe");		
		return 1;
	}

	int pid = fork();
	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}

	int efd = epoll_create(1);
	if(efd == -1)
	{
		perror("epoll_create");	
		return 1;
	}

	if(pid == 0)
	{
		close(fd[1]);
		struct epoll_event ev, evs[1];
		ev.events = EPOLLIN;
		ev.data.fd = fd[0];
		epoll_ctl(efd, EPOLL_CTL_ADD, fd[0], &ev);
		while(1)
		{
			printf("epoll_wait 正在阻塞......\n");
			int n = epoll_wait(efd, evs, 1, -1);
			if(n <= 0)
			{
				perror("epoll_wait");	
				exit(1);
			}
			printf("read 正在阻塞......\n");
			char buf[1024] = "";
			int num = read(fd[0], buf, sizeof(buf));	
			if(num <= 0)
			{
				perror("read");	
				close(fd[0]);
				exit(0);
			}
			write(STDOUT_FILENO, buf, num);
			putchar('\n');
		}
	}
	else
	{
		close(fd[0]);	
		struct epoll_event ev;
		
		while(1)
		{	
			close(fd[0]);
			char buf[5];
			char ch='a';
			while(1)
			{
				sleep(3);
				memset(buf,ch++,sizeof(buf));
				write(fd[1],buf,5);
			}
		}

	}

	return 0;
}
