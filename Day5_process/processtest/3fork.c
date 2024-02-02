#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int status = -1;
	int ret = -1;
	pid_t pid = fork();
	int* p = NULL;
	p = malloc(sizeof(int) * 5);
	if (pid == 0)
	{
		for (int i = 0; i < 30; i++)
		{
			printf("pid is %d   ", getpid());
			printf("the son process is doing %d\n", i + 1);
			sleep(1);
		}
		p[0] = 1;
		printf("%ls\n", p);
		exit(10);
	}	

	ret = wait(&status);

	if(WIFEXITED(status))
	{
		printf("子进程退出状态码: %d\n", WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status))
	{
		printf("子进程被信号 %d kill 了...\n", WTERMSIG(status));
	}

	printf("the pointer is %ls\n", p);
	return 0;
}
