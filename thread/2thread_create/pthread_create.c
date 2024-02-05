#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>


void* func(void* arg)
{
	int num = (int)(long)arg;
	printf("new thread num is %d\n", num);
	return NULL;
}

int main(void)
{
	pthread_t tid;

	int ret = pthread_create(&tid, NULL, func, (void*)(0x03));
	if(ret != 0)
	{
		printf("pthread_create error\n");	
		return 1;
	}

	pthread_join(tid, NULL);

	return 0;
}
