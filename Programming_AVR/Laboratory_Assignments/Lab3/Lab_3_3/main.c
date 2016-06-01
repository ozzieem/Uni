#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd4.h"

lcd4 theDisplay;

void dec_to_bin(int sw_value, char * sw_bin);

int main(void)
{
	DDRA = 0x00;
	lcd4_init(&theDisplay, &PORTB, &DDRB, 4000, 100);

	int sw_value = 0;
	char s[20];
	
	while (1)
	{
		sw_value = PINA;
		print_to_lcd(s, sw_value);
	}
	return 0;
}

void print_to_lcd(char s[], int sw_value)
{
	// PRINT HEX
	sprintf(s, "HEX = %02x", 0xFF - sw_value);
	lcd4_cup_row1(&theDisplay);
	lcd4_write_string(&theDisplay, s);
	
	// CALCULATE BINARY
	char sw_bin[9];
	dec_to_bin(sw_value, sw_bin);

	// PRINT BINARY
	sprintf(s,"BIN = %s", sw_bin);
	lcd4_cup_row2(&theDisplay);
	lcd4_write_string(&theDisplay, s);

	for (int i = 0; i <= 8; i++)
	{
		sw_bin[i] = 48;
	}
}

void dec_to_bin(int sw_value, char * sw_bin)
{
	int dec, i = 0;
	dec = 255 - sw_value;
	while(i < 8)
	{
		sw_bin[7-i] = dec % 2 + '0';
		dec /= 2;
		i++;
	}
	sw_bin[8] = '\0';
}
