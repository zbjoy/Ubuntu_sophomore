#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
		execlp("ls", "ls", "-l", "/home", NULL);	
		exit(0);
	}

	wait(NULL);
	return 0;
}
