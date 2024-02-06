#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>

void* func1(void* arg)
{
	pthread_mutex_t* mutex = arg;

	pthread_mutex_lock(&mutex[0]);
	printf("线程1已经占用资源1...\n");
	pthread_mutex_lock(&mutex[1]);

	printf("线程1已经执行...\n");

	pthread_mutex_unlock(&mutex[0]);
	pthread_mutex_unlock(&mutex[1]);
}

void* func2(void* arg)
{
	pthread_mutex_t* mutex = arg;

	pthread_mutex_lock(&mutex[1]);
	printf("线程2已经占用资源2...\n");
	pthread_mutex_lock(&mutex[0]);

	printf("线程2已经执行...\n");

	pthread_mutex_unlock(&mutex[0]);
	pthread_mutex_unlock(&mutex[1]);
}

int main(void)
{

	pthread_t tid1;
	pthread_t tid2;

	pthread_mutex_t mutex[2];
	//pthread_mutex_t mutex2;

	pthread_mutex_init(&mutex[0], NULL);
	pthread_mutex_init(&mutex[1], NULL);

	pthread_create(&tid1, NULL, func1, mutex);
	pthread_create(&tid2, NULL, func2, mutex);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_mutex_destroy(&mutex[0]);
	pthread_mutex_destroy(&mutex[1]);
	return 0;
}

