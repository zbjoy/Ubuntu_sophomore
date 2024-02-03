#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

int main(void)
{
	printf("hello world\n");
	execlp("ls", "ls", "-l", "/home/zbjoy", NULL);
	printf("hello execlp\n");
	return 0;
}
