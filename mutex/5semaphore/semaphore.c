#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t sem_produce;
sem_t sem_custom;

typedef struct _node
{
	int data;
	struct _node* next;
}Node;

Node* head = NULL;

void* produce(void* arg)
{
	while(1)	
	{
		sem_wait(&sem_produce);	

		Node* p = (Node*)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = head;
		head = p;

		printf("生产者生产一个 %d.....\n", p->data);

		sem_post(&sem_custom);

		sleep(rand() % 3 + 1);
	}

	pthread_exit(NULL);
}

void* custom(void* arg)
{
	while(1)
	{
		sem_wait(&sem_custom);

		Node* tmp = head;
		head = head->next;

		printf("消费者消费一个 %d.....\n", tmp->data);

		free(tmp);

		sem_post(&sem_produce);

		sleep(rand() % 3 + 1);
	}
}

int main(void)
{
	srand(getpid());
	sem_init(&sem_produce, 0, 6);
	sem_init(&sem_custom, 0, 0);

	pthread_t tid[9];

	for(int i = 0; i < 9; i++)
	{
		if(i < 6)
		{
			pthread_create(&tid[i], NULL, produce, NULL);		
		}
		else
		{
			pthread_create(&tid[i], NULL, custom, NULL);	
		}
	}

	for(int i = 0; i < 9; i++)
	{
		if(i < 6)
		{
			pthread_join(tid[i], NULL);		
		}
		else
		{
			pthread_join(tid[i], NULL);	
		}
	}

	sem_destroy(&sem_produce);
	sem_destroy(&sem_custom);
	return 0;
}
