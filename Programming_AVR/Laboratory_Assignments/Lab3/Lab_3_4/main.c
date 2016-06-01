#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd4.h"

lcd4 theDisplay;

const int DICE_MAX = 6;

int main(void)
{
	DDRA = 0x00;
	lcd4_init(&theDisplay, &PORTB, &DDRB, 4000, 100);

	int sw_button = 0;
	
	while (1)
	{
		sw_button = (PINA & 0x01) == 0;
		if(sw_button)
			print_to_lcd();
	}
	return 0;
}

void print_to_lcd()
{
	char s[20];
	int diceValue = rand() % DICE_MAX + 1;

	sprintf(s, "Dice Dec = %d", diceValue);
	lcd4_cup_row1(&theDisplay);
	lcd4_write_string(&theDisplay, s);
}