#include <stdio.h>
#include "piodirect.h"
#include "pwm.h"

typedef enum
{
	ZERO,
	TWENTYFIVE,
	FIFTY,
	SEVENTYFIVE,
	HUNDRED
}LedBrightness;

void lighter(LedBrightness ledBrightness, PWM pwm)
{
	switch (ledBrightness)
	{
	case ZERO:
		{
			pwmPulse(pwm, 0.0);
			break;
		}
	case TWENTYFIVE:
		{
			pwmPulse(pwm, 0.25);
			break;
		}
	case FIFTY:
		{
			pwmPulse(pwm, 0.5);
			break;
		}
	case SEVENTYFIVE:
		{
			pwmPulse(pwm, 0.75);
			break;
		}
	case HUNDRED:
		{
			pwmPulse(pwm, 1.0);
			break;
		}
	default:
		break;
	}
}

#if 1
int main()
{
	gpioSetup();
	PWM led_5, led_4;
	led_5 = pwmCreate(_5, 100);
	led_4 = pwmCreate(_4, 100);

	LedBrightness yellowBrightness;
	yellowBrightness = ZERO;
	LedBrightness greenBrightness;
	greenBrightness = ZERO;

	GPIO button_12 = createWithPullUpDown(_12, PUD_UP);
	GPIO button_13 = createWithPullUpDown(_13, PUD_UP);

	int old_button_12 = 0;
	int old_button_13 = 0;

	while (1)
	{
		if (!readIn(button_12) != old_button_12)
		{
			if (!readIn(button_12))
			{
				if (yellowBrightness == HUNDRED)
				{
					yellowBrightness = ZERO;
				}
				else
					yellowBrightness++;
			}
			old_button_12 = !readIn(button_12);
		}

		if (!readIn(button_13) != old_button_13)
		{
			if (!readIn(button_13))
			{
				if (greenBrightness == HUNDRED)
				{
					greenBrightness = ZERO;
				}
				else
					greenBrightness++;
			}
			old_button_13 = !readIn(button_13);
		}

		lighter(yellowBrightness, led_4);
		lighter(greenBrightness, led_5);
	}
	destroy(button_12);
	destroy(button_13);
	pwmDestroy(led_4);
	pwmDestroy(led_5);
	return 0;
}
#endif // 1