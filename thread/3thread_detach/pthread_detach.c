#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>
#include <unistd.h>

void* func(void* arg)
{
	for(int i = 0; i < 5; i++)
	{
		printf("the thread is working...\n");	
		sleep(1);
	}
	return NULL;
}

int main(void)
{
	pthread_t tid;

	int ret = pthread_create(&tid, NULL, func, NULL);

	if(ret != 0)
	{
		printf("pthread_create: %s\n", strerror(ret));	
		return 1;
	}

	printf("等待回收线程资源...\n");
	pthread_detach(tid);

	while(1);

	return 0;
}
