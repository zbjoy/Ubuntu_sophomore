#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>

int main(void)
{	
	int fd = -1;
	fd = open("test.txt", O_RDWR );
	if(fd == -1)
	{
		perror("open test.txt");	
		return 1;
	}


	int len = lseek(fd, 0, SEEK_END);
	void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");	
		return 1;
	}

	close(fd);

	printf("buf = %s\n", (char*)ptr);

	strcpy((char*)ptr, "this is a test");

	int ret = munmap(ptr, len);
	if(ret == -1)
	{
		perror("munmap");	
		exit(1);
	}
	return 0;
}
