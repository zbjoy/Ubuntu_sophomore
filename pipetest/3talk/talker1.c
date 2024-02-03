#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define SIZE 128

int main(void)
{
	int fdr = -1;
	int fdw = -1;
	pid_t pidwrite = -1;
	pid_t pidread = -1;
	char buf[SIZE];
	pidread = fork();
	if(pidread == -1)
	{
		perror("fork pidread");	
		return 1;
	}

	printf("pidread进程创建成功...\n");

	if(pidread == 0)
	{
		int ret = -1;
		ret = access("fifo1", F_OK);	
		if(ret == -1)
		{
			if(-1 == mkfifo("fifo1", 0664))
			{
				perror("mkfifo fifo1");	
				exit(0);
			}	
		}

		fdr = open("fifo1", O_RDONLY);
		if(fdr == -1)
		{
			perror("open fifo1");	
			exit(0);
		}

		while(1)
		{
			memset(buf, 0, SIZE);	
			if(0 >= read(fdr, buf, SIZE));
			{
				perror("read fifo1");	
				exit(1);
			}

			printf("talker2 say: %s\n", buf);
		}
	
	}

	pidwrite = fork();
	if(pidwrite == -1)
	{
		perror("fork pidwrite");	
		return 1;
	}

	printf("pidwrite进程创建成功...\n");
	if(pidwrite == 0)
	{
		int ret = -1;
		ret = access("fifo2", F_OK);	
		if(ret == -1)
		{
			if(-1 == mkfifo("fifo2", 0664))
			{
				perror("mkfifo fifo2");	
				exit(0);
			}	
		}

		fdw = open("fifo2", O_WRONLY);
		if(fdr == -1)
		{
			perror("open fifo2");	
			exit(0);
		}

		printf("fifo2 write 连接成功...\n");
		while(1)
		{
			memset(buf, 0, SIZE);	
			fgets(buf, SIZE, stdin);
			if(buf[strlen(buf) - 1] == '\n')
			{
				buf[strlen(buf) - 1] = '\0';	
			}
			if(0 >= write(fdw, buf, strlen(buf)));
			{
				perror("write fifo2");	
				exit(1);
			}

		}
	
	}
	int status = -1;
	wait(&status);

	return 0;
}
