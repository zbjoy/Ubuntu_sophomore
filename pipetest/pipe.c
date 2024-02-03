#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#define SIZE 64

int main(void)
{
	int fds[2];
	int ret = pipe(fds);
	pid_t pid = fork();
	
	if (pid == -1)	
	{
		perror("fork");
		return 1;
	}

	char buf[SIZE];
	if (pid == 0)
	{
		close(fds[1]);
		while(1)
		{
			int ret = -1;
			ret = read(fds[0], buf, SIZE);
			if(ret == -1 || ret == 0)	
			{
				close(fds[0]);
				perror("read");
				exit(0);
			}
			
			printf("read is : %s\n", buf);
			memset(buf, 0, SIZE);
		}
	}

	close(fds[0]);
	memset(buf, 0, SIZE);
	strcpy(buf, "hello world\n");	
	write(fds[1], buf, SIZE);
	printf("已经写入...\n");

	close(fds[1]);
	return 0;
}
