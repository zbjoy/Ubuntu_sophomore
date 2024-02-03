#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 128

int main(void)
{
	int fdw = -1;
	int fdr = -1;
	pid_t pid = -1;
	char buf[SIZE];

	if(-1 == access("fifo1", F_OK))
	{
		if(-1 == mkfifo("fifo1", 0664))	
		{
			perror("mkfifo fifo1");	
			return 1;
		}
	}


	if(-1 == access("fifo2", F_OK))
	{
		if(-1 == mkfifo("fifo2", 0664))	
		{
			perror("mkfifo fifo2");	
			return 1;
		}
	}
	
	pid = fork();
	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}

	if(pid == 0)
	{
		fdr = open("fifo1", O_RDONLY);	
		if(fdr == -1)
		{
			perror("open fifo1 read");	
			exit(0);
		}

		while(1)
		{
			memset(buf, 0, SIZE);
			int ret = read(fdr, buf, SIZE);	
			if(ret <= 0)
			{
				perror("read fifo1");	
				close(fdr);
				exit(1);
			}

			printf("talker2 say: %s\n", buf);
		}
	}

	fdw = open("fifo2", O_WRONLY);
	if(fdw == -1)
	{
		perror("ope fifo2");	
		return 1;
	}

	while(1)
	{
		memset(buf, 0, SIZE);	
		fgets(buf, SIZE, stdin);
		buf[strlen(buf) - 1] = '\0';

		int ret = write(fdw, buf, strlen(buf));
		if(ret <= 0)
		{
			perror("write fifo2");	
			close(fdw);
			return 1;
		}
	}

	return 0;		
}













