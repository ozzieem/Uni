#include <stdio.h>
#include <pThread.h>
#include <time.h>
#include "piodirect.h"

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

void* t2_function(GPIO* output)
{
	for (int i = 0; i < 1000; i++)
	{
		struct timespec ts;
		ts.tv_sec = 0;
		ts.tv_nsec = 5000000L;
		onOff(*output, ON);
		busy_wait(1000000);
		onOff(*output, OFF);
		nanosleep(&ts, NULL);
	}
}

int main()
{
	gpioSetup();
	GPIO led_4, led_5;
	led_4 = create(_4, OUT_PIN);
	led_5 = create(_5, OUT_PIN);

	pthread_t t1, t2;

	pthread_create(&t1, NULL, t1_function, &led_4);
	pthread_create(&t2, NULL, t2_function, &led_5);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	destroy(led_4);
	destroy(led_5);
}
#endif // 0