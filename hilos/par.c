#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int s=0;

sem_t s1, s2;

pthread_t h1,h2;

static void *f1();
static void *f2();

int main()
{

	sem_init(&s1, 0, 1);
	sem_init(&s2, 0, 0);

	pthread_create(&h1, NULL, *f1, NULL);
	pthread_create(&h2, NULL, *f2, NULL);

	pthread_join(h1, NULL);
	pthread_join(h2, NULL);

	return 0;
}

static void *f1()
{
	for(int i=0;i<=50;i++)
	{
		sem_wait(&s1);
		printf("%d\n", i);
		if(i % 2 == 0)
		{
			sem_post(&s2);
		}else{
			sem_post(&s1);
		}
	}
	s = 1;
}

static void *f2()
{
	while(s == 0)
	{
		sem_wait(&s2);
		printf("Par\n");
		sem_post(&s1);
	}
}
