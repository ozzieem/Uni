#include "AccLCD.h"

void AccLCD_init(AccLCD* accLcd)
{
	lcd4_init(&accLcd->lcdDisplay, &PORTB, &DDRB, 4000, 100);
}

void AccLCD_display(AccLCD* accLcd, Accelerator* acc)
{
	sprintf(accLcd->s, "Value = %d    ", acc->value);
	lcd4_cup_row1(&accLcd->lcdDisplay);
	lcd4_write_string(&accLcd->lcdDisplay, accLcd->s);
}