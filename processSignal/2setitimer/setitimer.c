#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/time.h>
#include <unistd.h>

int main(void)
{
	struct itimerval new_value;

	new_value.it_value.tv_sec = 3;
	new_value.it_value.tv_usec = 0;

	new_value.it_interval.tv_sec = 2;
	new_value.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &new_value, NULL);

	while(1)
	{
		printf("the process is waiting...\n");	
		sleep(1);
	}
	return 0;
}
