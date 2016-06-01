#include <stdio.h>

#include "Dice.h"
#include "Dice_LCD.h"
#include "Dice_LEDS.h"
#include "UsedLibraries\io_di.h"

int main(void)
{
	io_di button;

	Dice dice1, dice2;
	DiceLCD diceLcd;
	DiceLEDS diceLeds = {0x08, 0x82, 0x52, 0xC6, 0xD6, 0xEE};

	io_di_init(&button, &PORTA, 0x01);

	dice_init(&dice1);
	dice_init(&dice2);
	diceLEDS_init(&diceLeds);
	DiceLCD_init(&diceLcd);

	while (1)
	{
		char ioButton = io_di_read(&button);

		if(!ioButton)
		{
			dice_throw(&dice1);
			dice_throw(&dice2);

			diceLEDS_display(&diceLeds, &dice1);
			DiceLCD_display(&diceLcd, &dice1, &dice2);
		}
	}
	return 0;
}
