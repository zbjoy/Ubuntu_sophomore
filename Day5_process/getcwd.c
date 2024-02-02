#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 128

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage: a.out filePath\n");
		return 1;
	}
	char buf[SIZE];
	memset(buf, 0, SIZE);

	if (NULL == getcwd(buf, SIZE))
	{
		perror("getcwd");
		return 1;
	}

	printf("getcwd is %s\n", buf);

	if ( chdir(argv[1]) == -1)
	{
		perror("chdir");
		return 1;
	}

	memset(buf, 0, SIZE);
	if (NULL == getcwd(buf, SIZE))
	{
		perror("getcwd");
		return 1;
	}

	printf("after chdir : %s\n", buf);

	return 0;
}
