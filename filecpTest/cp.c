#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 128

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("usage:./a.out srcfilePath objfilePath");
		return 1;
	}

	int fd = -1;
	int ofd = -1;
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open srcfilePath");
		return 1;
	}

	ofd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if(ofd == -1)
	{
		perror("open objfilePath");
		return 1;
	}

	char buf[SIZE];
	memset(buf, 0, SIZE);
	int ret = 0;
	while((ret = read(fd, buf, SIZE)) > 0)
	{
		if(-1 == write(ofd, buf, ret))
		{
			perror("write");
			return 1;
		}
		memset(buf, 0, SIZE);
	}

	close(fd);
	close(ofd);

	return 0;
}
