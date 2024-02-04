#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>

int print_set(sigset_t* set)
{
	
	for(int i = 1; i < 32; i++)
	{
		if(sigismember(set, i))	
		{
			printf("1");	
		}
		else
		{
			printf("0");	
		}
	}
	putchar('\n');
}

int main(void)
{
	sigset_t set;
	sigemptyset(&set);	
	print_set(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	print_set(&set);
	sigfillset(&set);
	print_set(&set);
	sigdelset(&set, SIGINT);
	sigdelset(&set, SIGQUIT);
	print_set(&set);
	return 0;
}
