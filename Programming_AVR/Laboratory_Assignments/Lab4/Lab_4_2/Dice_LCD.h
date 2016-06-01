#ifndef DICE_LCD_H_
#define DICE_LCD_H_

#include <util/delay.h>
#include "UsedLibraries\lcd4.h"
#include "Dice.h"

typedef struct
{
	char s[20];
	lcd4 lcdDisplay;
	
} DiceLCD;

void diceLCD_init(DiceLCD*);
void diceLCD_display(DiceLCD*, Dice*, Dice*);

#endif /* DICE_LCD_H_ */