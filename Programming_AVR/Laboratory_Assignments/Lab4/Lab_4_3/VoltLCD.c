#include "VoltLCD.h"

void voltLCD_init(VoltLCD* vlcd)
{
	lcd4_init(&vlcd->lcdDisplay, &PORTB, &DDRB, 4000, 100);
}

void voltLCD_display(VoltLCD* vlcd, long volts)
{
	sprintf(vlcd->s, "U = %d  ", volts);
	lcd4_cup_row1(&vlcd->lcdDisplay);
	lcd4_write_string(&vlcd->lcdDisplay, vlcd->s);
}