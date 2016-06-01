#include <stdio.h>
#include <time.h>
#include "piodirect.h"

#if 0
int main(int argc, char *argv[])
{
	gpioSetup();
	GPIO led_4 = create(_4, OUT_PIN);
	struct timespec lightOn, lightOff;

	lightOn.tv_sec = 0;
	lightOff.tv_sec = 0;
	lightOn.tv_nsec = 20000000L;
	lightOff.tv_nsec = 20000000L;

	for (int i = 0; i < 100; i++)
	{
		onOff(led_4, ON);
		nanosleep(&lightOn, NULL);
		onOff(led_4, OFF);
		nanosleep(&lightOff, NULL);
	}
	destroy(led_4);
	return 0;
}
#endif // 0