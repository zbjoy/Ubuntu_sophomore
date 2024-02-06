#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int num = 1;

void* funcread(void* arg)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("thread read is %d...\n", num);	
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

void* funcwrite(void* arg)
{
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		num++;
		printf("thread write is %d...\n", num);	
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

int main(void)
{
	int ret = pthread_rwlock_init(&rwlock, NULL);
	if(ret != 0)
	{
		printf("pthread_rwlock_init %s\n", strerror(ret));	
		return 1;
	}

	pthread_t tidread[4];
	pthread_t tidwrite[2];

	for(int i = 0; i < 4; i++)
	{
		pthread_create(&tidread[i], NULL, funcread, NULL);	
	}

	for(int i = 0; i < 2; i++)
	{
		pthread_create(&tidwrite[i], NULL, funcwrite, NULL);	
	}

	for(int i = 0; i < 6; i++)
	{
		if(i < 4)	
		{
			pthread_join(tidread[i], NULL);	
		}
		else
		{	
			pthread_join(tidwrite[i - 4], NULL);
		}
	}
	pthread_rwlock_destroy(&rwlock);


	return 0;
}
