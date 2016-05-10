#define BILLION 1000000000L

#include <stdio.h>
#include <pThread.h>
#include <time.h>
#include "piodirect.h"

void busy_wait(const long nsec)
{
	long diffns = 0;
	int diffs = 0;
	struct timespec ts1, ts2;

	clock_gettime(0, &ts1);
	clock_gettime(0, &ts2);

	while (diffns < nsec)
	{
		clock_gettime(0, &ts2);
		diffns = ts2.tv_nsec - ts1.tv_nsec;
		diffs = ts2.tv_sec - ts1.tv_sec;
		diffns += diffs * BILLION;
	}
}

#if 0

void* t1_function(GPIO* output)
{
	for (int i = 0; i < 1000; i++)
	{
		onOff(*output, ON);
		busy_wait(1000000);
		onOff(*output, OFF);
		busy_wait(3000000);
	}
}

int main()
{
	gpioSetup();
	GPIO led_4;
	led_4 = create(_4, OUT_PIN);

	pthread_t t1;
	pthread_create(&t1, NULL, t1_function, &led_4);

	pthread_join(t1, NULL);
	onOff(led_4, OFF);

	destroy(led_4);
}
#endif // 0