#include <pthread.h>
#include <stdio.h>

#define MAX_NUM 1000000
volatile int counter;
int results[MAX_NUM], top;

pthread_mutex_t mtx;

void * t1func(void *args)
{
	while (counter <= MAX_NUM)
	{
		pthread_mutex_lock(&mtx);
		counter++;
		pthread_mutex_unlock(&mtx);
	}
}

void * t2func(void *args)
{	
	while (1)
	{	
		pthread_mutex_lock(&mtx);
		if ((counter % 2) != 0)
		{   
			results[top++] = counter;
		}
		
		if (counter >= MAX_NUM)
		{
			break;
		}
		pthread_mutex_unlock(&mtx);
	}	
}
int main(int argc, char *argv []) 
{
	pthread_t thread1, thread2;
	int i, totalOdds;

	pthread_mutex_init(&mtx, NULL);
	
	counter = top = 0;
	for (i = 0; i < MAX_NUM; ++i)
	{
		results[i] = 0;
	}
	
	pthread_create(&thread1, NULL, t1func, NULL);
	pthread_create(&thread2, NULL, t2func, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("Even Numbers:\n");
	for (i = 0; i < MAX_NUM; ++i)
	{
		if (results[i] != 0 && (results[i] % 2) == 0)
		{
			printf("%d\n", results[i]);
		}
		else if((results[i] % 2) != 0)
		{
			totalOdds++;
		}
	}
	
	printf("Total Odd Numbers: %d\n", totalOdds);
	
	pthread_mutex_destroy(&mtx);
	
	return 0;
}