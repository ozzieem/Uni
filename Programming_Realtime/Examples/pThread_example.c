#include <pThread.h>

void *foo(void *args)
{
	for(int i = 0; i < 10; i++)
	{
		printf("Thread ran\n");
	}
}

int main()
{
	pthread_t t;
	pthread_create(&t, NULL, foo, NULL);
	printf("Main\n");
	pthread_join(t, NULL);
}