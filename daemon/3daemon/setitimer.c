#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void write_time(int num)
{
	printf("hello %d\n", num);
}

int main(void)
{
	struct sigaction sigact;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = write_time;
	sigaction(SIGALRM, &sigact, NULL);

	struct itimerval act;

	act.it_interval.tv_sec = 2;
	act.it_interval.tv_usec = 0;
	// 设置第一次触发定时器时间
	act.it_value.tv_sec = 2;
	act.it_value.tv_usec = 0;
	// 开始计时
	setitimer(ITIMER_REAL, &act, NULL);

	while(1)
	{
			
	}
	return 0;
}
