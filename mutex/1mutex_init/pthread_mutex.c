#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>
#include <unistd.h>


void* func(void* arg)
{
	pthread_mutex_t* pmutex = arg;

	pthread_mutex_lock(pmutex);

	for(int i = 'A'; i <= 'Z'; i++)
	{
		printf("%c", i);	
		fflush(stdout);
		usleep(100000);
	}

	pthread_mutex_unlock(pmutex);

	return NULL;
}

void* func2(void* arg)
{
	pthread_mutex_t* pmutex = arg;

	pthread_mutex_lock(pmutex);

	for(int i = 'a'; i <= 'z'; i++)
	{
		printf("%c", i);	
		fflush(stdout);
		usleep(100000);
	}

	pthread_mutex_unlock(pmutex);

	return NULL;
}

int main(void)
{
	pthread_mutex_t mutex;
	pthread_t tid;
	pthread_t tid2;


	int ret = pthread_mutex_init(&mutex, NULL);
	if(ret != 0)
	{
		printf("pthread_mutex_init %s", strerror(ret));	
		return 1;
	}


	ret = pthread_create(&tid, NULL, func, &mutex);
	if(ret != 0)
	{
		printf("pthread_create %s", strerror(ret));	
		return 1;
	}
	
	
	ret = pthread_create(&tid2, NULL, func2, &mutex);
	if(ret != 0)
	{
		printf("pthread_create %s", strerror(ret));	
		return 1;
	}


	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}
