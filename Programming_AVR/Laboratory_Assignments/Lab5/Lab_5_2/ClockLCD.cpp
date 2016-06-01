#include "ClockLCD.h"

ClockLCD::ClockLCD() 
{
	lcd4_init(&this->lcd, &PORTB, &DDRB, 700, 50);
}

void ClockLCD::DisplayClock(int hours, int minutes, int seconds)
{
	char s[20];
	sprintf(s, "%d:%d:%d   ", hours, minutes, seconds);

	lcd4_cup_row1(&this->lcd);
	lcd4_write_string(&this->lcd, s);
}