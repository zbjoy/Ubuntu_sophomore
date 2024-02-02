#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage: ./a.out filePath\n");
		return 1;
	}
	int fd = -1;
	fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd == -1)
	{
		perror("open()");
		return 1;
	}

	int newFd;
	newFd = dup(1);

	printf("newFd is : %d\n", newFd);
	char* buf = "hello dup\n";
	write(newFd, buf, strlen(buf));

	close(newFd);
	return 0;
}
