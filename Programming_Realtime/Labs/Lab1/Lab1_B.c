#include <stdio.h>
#include "piodirect.h"

#if 0
int main()
{
	gpioSetup();
	GPIO led_4 = create(_4, OUT_PIN);
	for (int i = 0; i < 10; i++)
	{
		onOff(led_4, ON);
		sleep(1);
		onOff(led_4, OFF);
		sleep(1);
	}
	destroy(led_4);
	return 0;
}

#endif