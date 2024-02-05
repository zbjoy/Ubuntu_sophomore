#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void printMode(struct stat* s)
{
	switch (s->st_mode & S_IFMT)
	{
		case S_IFSOCK:
			printf("s");
			break;
		case S_IFLNK:
			printf("l");
			break;
		case S_IFREG:
			printf("-");
			break;
		case S_IFBLK:
			printf("b");
			break;
		case S_IFDIR:
			printf("d");
			break;
		case S_IFCHR:
			printf("c");
			break;
		case S_IFIFO:
			printf("p");
			break;
		default:
			perror("have not this file type!!!\n");
	}

	if (s->st_mode & S_IRUSR)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IWUSR)
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IXUSR)
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IRGRP)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IWGRP)
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IXGRP)
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IROTH)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IWOTH)
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	
	if (s->st_mode & S_IXOTH)
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
}	

void printStat(struct stat* s)
{
	printMode(s);
	putchar('\n');
	printf("st_dev is : %lu\n", s->st_dev);
	printf("st_ino is : %ld\n", s->st_ino);
	printf("st_nlink is : %ld\n", s->st_nlink);
	printf("st_uid is : %d\n", s->st_uid);
	printf("st_gid is : %d\n", s->st_gid);
	printf("st_rdev is : %ld\n", s->st_rdev);
	printf("st_size is : %lu\n", s->st_size);
	printf("st_blksize is : %lu\n", s->st_blksize);
	printf("st_blocks is : %ld\n", s->st_blocks);
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("./a.out filePath\n");
		return 1;
	}
	int fd = -1;
	fd  = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open()");
		return 1;
	}

	struct stat s;
	stat(argv[1], &s);

	printStat(&s);
	return 0;
}
