#include <stdio.h>
#include "piodirect.h"

#if 0
int main(int argc, char *argv[])
{
	gpioSetup();
	GPIO button_4 = createWithPullUpDown(_4, PUD_UP);
	GPIO button_5 = createWithPullUpDown(_5, PUD_UP);
	GPIO led_12 = create(_12, OUT_PIN);
	GPIO led_13 = create(_13, OUT_PIN);
	int oldYellowButton = 0;
	int oldGreenButton = 0;
	int yellowLed = 0;
	int greenLed = 0;
	onOff(led_12, OFF);
	onOff(led_13, OFF);

	while (1)
	{
		if (!readIn(button_4) != oldYellowButton || !readIn(button_5) != oldGreenButton)
		{
			if (!readIn(button_4))
			{
				if (yellowLed)
				{
					onOff(led_12, OFF);
					yellowLed = 0;
				}
				else
				{
					onOff(led_12, ON);
					yellowLed = 1;
				}
			}
			if (!readIn(button_5))
			{
				if (greenLed)
				{
					onOff(led_13, OFF);
					greenLed = 0;
				}
				else
				{
					onOff(led_13, ON);
					greenLed = 1;
				}
			}

			oldYellowButton = !readIn(button_4);
			oldGreenButton = !readIn(button_5);
		}
	}
	destroy(button_4);
	destroy(button_5);
	destroy(led_12);
	destroy(led_13);

	return 0;
}
#endif // 0
