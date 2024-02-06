#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

typedef struct _node
{
	int data;
	struct _node* next;
}Node;

Node* head = NULL;

void* producer(void* arg)
{
	while(1)
	{
		Node* pnew = (Node*)malloc(sizeof(Node));
		pnew->data = rand() % 100 + 1;
		
		pthread_mutex_lock(&mutex);	

		printf("生产者添加 %d.....\n", pnew->data);
		pnew->next = head;
		head = pnew;

		pthread_mutex_unlock(&mutex);

		pthread_cond_signal(&cond);

		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}

void* customer()
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(head == NULL)	
		{
			pthread_cond_wait(&cond, &mutex);	
		}
		
		Node* tmp = head;
		head = head->next;

		printf("消费者消费 %d.....\n", tmp->data);

		free(tmp);
		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

int main(void)
{
	srand(getpid());
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_t tid_pro;
	pthread_t tid_cus;

	pthread_create(&tid_pro, NULL, producer, NULL);
	pthread_create(&tid_cus, NULL, customer, NULL);

	pthread_join(tid_pro, NULL);
	pthread_join(tid_cus, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
