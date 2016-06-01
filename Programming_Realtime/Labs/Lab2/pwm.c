#include <time.h>
#include <stdio.h>
#include "piodirect.h"
#include "pwm.h"

#define BILLION 1000000000L

PWM pwmCreate(enum Pin pin, unsigned int frequency)
{
	PWM pwm;
	pwm.frequency = frequency;
	pwm.pio = create(pin, OUT_PIN);
	return pwm;
}

int pwmPulse(PWM pwm, float dutyPercent)
{
	struct timespec lightOn, lightOff;
	lightOn.tv_sec = 0;
	lightOff.tv_sec = 0;
	lightOn.tv_nsec = 1.0 / pwm.frequency * dutyPercent * BILLION;
	lightOff.tv_nsec = 1.0 / pwm.frequency * (1.0 - dutyPercent) * BILLION;

	if (dutyPercent > 0)
	{
		onOff(pwm.pio, ON);
		nanosleep(&lightOn, NULL);
	}
	onOff(pwm.pio, OFF);
	nanosleep(&lightOff, NULL);

	return 0;
}

int pwmDestroy(PWM pwm)
{
	destroy(pwm.pio);
}