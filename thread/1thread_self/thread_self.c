#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>

int main(void)
{
	pthread_t tid;
	
	tid = pthread_self();
	printf("tid = %lu\n", tid);
	
	int ret = pthread_equal(tid, pthread_self());
	if(ret == 0)
	{
		printf("pthread_equal error\n");	
		return 1;
	}

	printf("is equal\n");

	return 0;
}
