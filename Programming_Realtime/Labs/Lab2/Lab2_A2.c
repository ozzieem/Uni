#include <stdio.h>
#include "piodirect.h"
#include <time.h>
#include "pwm.h"

#define BREATHECYCLES 100

#if 0
int main(int argc, char *argv[])
{
	gpioSetup();
	PWM led_4, led_5;
	led_5 = pwmCreate(_5, 150);
	led_4 = pwmCreate(_4, 150);

	for (int j = 0; j < 10; j++)
	{
		for (float i = 0; i < BREATHECYCLES; i++)
		{
			pwmPulse(led_4, i / 100);
			pwmPulse(led_5, 1.0 - i / 100);
		}
		for (float i = BREATHECYCLES; i > 0; i--)
		{
			pwmPulse(led_4, i / 100);
			pwmPulse(led_5, 1.0 - i / 100);
		}
	}
	pwmDestroy(led_4);
	pwmDestroy(led_5);
	return 0;
}
#endif // 0