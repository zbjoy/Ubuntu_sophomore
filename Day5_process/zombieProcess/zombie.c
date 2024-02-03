#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid = fork();

	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}

	if(pid == 0)
	{

		for(int i = 0; i < 5; i++)
		{
					
			printf("子进程正在工作(%d)...\n", getpid());	
			sleep(1);
		}

		printf("子进程结束了\n");
		exit(0);
			
	}


	sleep(100);
	return 0;
}
