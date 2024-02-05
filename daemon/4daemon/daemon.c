#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

#define SIZE 64

void fun(int num)
{
	time_t t;
	t = time(NULL);
	struct tm* tm = NULL;

	tm = localtime(&t);

	char cmd[SIZE];
	memset(cmd, 0, SIZE);
	sprintf(cmd, "touch %d%d%d%d%d%dlog.txt", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

	system(cmd);

}

int main(void)
{
	int fd = -1;
	pid_t pid = -1;
	int ret = -1;
	
	pid = fork();
	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}
	
	if(pid > 0)
	{
		exit(0);	
	}

	setsid();

	struct sigaction act;

	act.sa_handler = fun;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	sigaction(SIGALRM, &act, NULL);



	struct itimerval value;
	value.it_interval.tv_sec = 2;
	value.it_interval.tv_usec = 0;
	value.it_value.tv_sec = 3;
	value.it_value.tv_usec = 0;

	ret = setitimer(ITIMER_REAL, &value, NULL);
	if(ret == -1)
	{
		perror("setitimer");	
		exit(1);
	}


	while(1);

	return 0;
}
