#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int ret = mkfifo("./fifowrite", 0664);
	if(ret == -1)
	{
		perror("mkfifowrite");	
		return 1;
	}
	
	int ret1 = mkfifo("./fiforead", 0664);
	if(ret1 == -1)
	{
		perror("mkfiforead");	
		return 1;
	}
	return 0;
}
