#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


void printStat(int fd)
{
	if (fd == -1)
	{
		perror("printStat(fd)");
		return;
	}

	int flag = fcntl(fd, F_GETFL);
	
	if (flag & O_APPEND)
	{
		printf("before 追加\n");
	}
	else
	{
		printf("bfore not 追加\n");
	}


	flag = flag | O_APPEND;
	flag = fcntl(fd, F_SETFL, flag);

	flag = fcntl(fd, F_GETFL);
	
	if (flag & O_APPEND)
	{
		printf("after 追加\n");
	}
	else
	{
		printf("after not 追加\n");
	}
}

int main(void)
{
	int fd = -1;
	int newfd = -1;
	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		perror("open()");
		return 1;
	}

	newfd = fcntl(fd, F_DUPFD, 0);
	if (newfd == -1)
	{
		perror("fcntl newfd");
		return 1;
	}

	printf("fd = %d\n", fd);
	printf("newfd = %d\n", newfd);

	printStat(fd);

	close(fd);
	close(newfd);

	return 0;
}
