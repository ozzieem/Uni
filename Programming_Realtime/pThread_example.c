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
	pThread_t t;
	pThread_create(&t, NULL, foo, NULL);
	printf("Main\n");
	pThread_join(t, NULL);
}