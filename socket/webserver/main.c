#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("usage: ./a.out port [respath]\n");
		return -1;
	}

	char respath[1024] = "";

	if(argc == 2)
	{
		sprintf(respath,  "./res");	
	}
	else
	{
		sprintf(respath, "%s", argv[2]);	
	}

	chdir(respath);
	epoll_run(atoi(argv[1]));
	return 0;
}
