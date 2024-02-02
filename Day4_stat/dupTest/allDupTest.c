#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int fd = -1;
	int newFd = -1;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}

	newFd = dup(1);

	if(dup2(fd, 1) != 1)
	{
		perror("dup2()");
		return 1;
	}

	close(fd);
	char buf[128];
	memset(buf, 0, 128);
	read(1, buf, 128);
	printf("read(1, buf, 128): %s\n", buf);

	dup2(newFd, 1);
	write(1, buf, 128);
	close(newFd);

	return 0;

}
