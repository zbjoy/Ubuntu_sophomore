#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int fd = -1;
	fd = open("test.txt", O_RDWR);
	int len = lseek(fd, 0, SEEK_END);

	void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");	
		return 1;
	}

	close(fd);

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}

	if(pid == 0)
	{
		sleep(1);
		printf("buf is %s\n", (char*)ptr);	
		exit(0);
	}

	strcpy((char*)ptr, "i am father process");
	wait(NULL);

	int ret = munmap(ptr, len);
	if(ret == -1)
	{
		perror("munmap");	
		return 1;
	}
	
	return 0;
}
