#include "Dice_LEDS.h"

diceLEDS_init(DiceLEDS* dleds)
{
	DDRD = 0xFF;
}

void diceLEDS_display(DiceLEDS* dleds, Dice* d)
{
	PORTD = 255 - dleds->leds[d->value - 1];
}

