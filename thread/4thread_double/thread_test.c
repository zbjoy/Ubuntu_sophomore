#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>
#include <unistd.h>

void* func(void* arg)
{
	for(int i = 'A'; i < 'Z'; i++)
	{
		printf("%c", i);	
		fflush(stdout);
		usleep(100000);
	}
	return NULL;
}

void* func2(void* arg)
{
	for(int i = 'a'; i < 'z'; i++)
	{
		printf("%c", i);	

		fflush(stdout);
		usleep(100000);
	}
	return NULL;
}

int main(void)
{
	pthread_t tid;
	pthread_t tid2;

	int ret = pthread_create(&tid, NULL, func, NULL);
	if(ret != 0)
	{
		printf("pthread_create %s\n", strerror(ret));	
		return 1;
	}

	ret = pthread_create(&tid2, NULL, func2, NULL);
	if(ret != 0)
	{
		printf("pthread_create %s\n", strerror(ret));	
		return 1;
	}

	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);
	putchar('\n');
	return 0;
}
