#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

int main(void)
{
	execl("/bin/ls", "ls", "-l", "/home/zbjoy", NULL);
	return 0;
}
