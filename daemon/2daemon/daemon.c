#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <time.h>

#define SIZE 64

int main(void)
{

	time_t t = -1;
	t = time(NULL);
	struct tm* time = NULL;

	time = localtime(&t);

	char cmd[SIZE];
	memset(cmd, 0, SIZE);
	sprintf(cmd, "touch %d%d%d%d%d%dlog.txt", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
	system(cmd);
	return 0;
}
