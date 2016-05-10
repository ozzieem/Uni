#include <stdio.h>
#include "piodirect.h"

#if 0
int main(int argc, char *argv[])
{
	gpioSetup();
	GPIO button_12 = createWithPullUpDown(_12, PUD_UP);
	GPIO button_13 = createWithPullUpDown(_13, PUD_UP);
	GPIO led_4 = create(_4, OUT_PIN);
	GPIO led_5 = create(_5, OUT_PIN);
	int oldYellowButton = 0;
	int oldGreenButton = 0;
	int yellowLed = 0;
	int greenLed = 0;
	onOff(led_4, OFF);
	onOff(led_5, OFF);

	while (1)
	{
		if (!readIn(button_12) != oldYellowButton || !readIn(button_13) != oldGreenButton)
		{
			if (!readIn(button_12))
			{
				if (yellowLed)
				{
					onOff(led_4, OFF);
					yellowLed = 0;
				}
				else
				{
					onOff(led_4, ON);
					yellowLed = 1;
				}
			}
			if (!readIn(button_13))
			{
				if (greenLed)
				{
					onOff(led_5, OFF);
					greenLed = 0;
				}
				else
				{
					onOff(led_5, ON);
					greenLed = 1;
				}
			}

			oldYellowButton = !readIn(button_12);
			oldGreenButton = !readIn(button_13);
		}
	}
	destroy(button_12);
	destroy(button_13);
	destroy(led_4);
	destroy(led_5);

	return 0;
}
#endif // 0