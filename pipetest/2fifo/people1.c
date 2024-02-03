#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define SIZE 128

int main(void)
{
	int fdr = -1;
	int fdw = -1;
	char buf[SIZE];

	fdr = open("fifo1", O_RDONLY);
	if(fdr == -1)
	{
		perror("openfifo1");
		return 1;
	}
	printf("成功打开fifo1......\n");

	fdw = open("fifo2", O_WRONLY);
	if(fdw == -1)
	{
		perror("openfifo2");	
		return 1;
	}

	printf("成功打开fifo2......\n");

	while(1)
	{
		memset(buf, 0, SIZE);
		int ret = read(fdr, buf, SIZE);		
		if(ret <= 0)
		{
			perror("read1");	
			return 1;
		}

		printf("people2 say: %s\n", buf);

		memset(buf, 0, SIZE);
		fgets(buf, SIZE, stdin);
		if(buf[strlen(buf)- 1] == '\n')
		{
			buf[strlen(buf) - 1] = '\0';	
		}
		ret = write(fdw, buf, strlen(buf));
		if(ret <= 0)
		{
			perror("write2");	
			return 1;
		}
	}
	return 0;
}
