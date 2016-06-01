#include "Dice_LCD.h"

void DiceLCD_init(DiceLCD* dlcd)
{
	lcd4_init(&dlcd->lcdDisplay, &PORTB, &DDRB, 4000, 100);
}

void DiceLCD_display(DiceLCD* dlcd, Dice* d1, Dice* d2)
{
	sprintf(dlcd->s, "Dice1 = %d", dice_value(d1));
	lcd4_cup_row1(&dlcd->lcdDisplay);
	lcd4_write_string(&dlcd->lcdDisplay, dlcd->s);

	sprintf(dlcd->s, "Dice2 = %d", dice_value(d2));
	lcd4_cup_row2(&dlcd->lcdDisplay);
	lcd4_write_string(&dlcd->lcdDisplay, dlcd->s);
}