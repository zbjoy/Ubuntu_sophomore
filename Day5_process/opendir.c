#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define SIZE 128

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage: a.out filePath\n");
		return 1;
	}
	
	DIR* ret = NULL;
	if ((ret = opendir(argv[1])) == NULL)
	{
		perror("opendir");
		return 1;
	}

	struct dirent* dir = NULL;

	char type[SIZE];
	memset(type, 0, SIZE);
	while (1)
	{
		if ((dir = readdir(ret)) == NULL)
		{
			perror("readdir");
			break;
		}


		printf("the name: %s    the type: ", dir->d_name);
		if (dir->d_type == DT_BLK)
		{
			printf("block device");
		}
		else if (dir->d_type == DT_CHR)
		{
			printf("character device");
		}
		else if (dir->d_type == DT_DIR)
		{
			printf("directory");
		}
		else if(dir->d_type == DT_FIFO)
		{
			printf("pipe");
		}
		else if (dir->d_type == DT_LNK)
		{
			printf("symbolic link");
		}
		else if (dir->d_type == DT_REG)
		{
			printf("regular file");
		}
		else if (dir->d_type == DT_SOCK)
		{
			printf("UNIX domain socket");
		}
		else if (dir->d_type == DT_UNKNOWN)
		{
			printf("could not be determined");
		}
		putchar('\n');
	}

	closedir(ret);

	return 0;
}
