#ifndef DICE_LEDS_H_
#define DICE_LEDS_H_

#include <avr/io.h>
#include "Dice.h"

typedef struct
{
	char leds[6];
} DiceLEDS;

void diceLEDS_init(DiceLEDS*);
void diceLEDS_display(DiceLEDS*, Dice*);

#endif /* DICE_LEDS_H_ */