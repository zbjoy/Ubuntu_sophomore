#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void)
{
	int len = 4096;
	void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");	
		return 1;
	}

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}

	if(pid == 0)
	{
		strcpy((char*)ptr, "hello mmap");	
		exit(0);
	}

	sleep(1);
	printf("the son said: %s\n ", (char*)ptr);

	int ret = munmap(ptr, len);
	if(ret == -1)
	{
		perror("munmap");	
		return 1;
	}
	return 0;
}
