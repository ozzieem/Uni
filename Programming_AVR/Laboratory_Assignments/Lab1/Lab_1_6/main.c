/*
 * Lab_1_6.c
 *
 * Created: 26/01/2016 12:07:41
 * Author : Oz
 */ 

#include <avr/io.h>

int dummy = 0x2312;

int main(void)
{
	init_func();
	
    while (1) 
    {
		loop_func();
		wait_milliseconds(200);
    }
}

/* 
void wait_milliseconds(int value);
const unsigned char LEDS[8]={0x00,0x81,0xC3,0xE7,0xFF,0xE7,0xC3,0x81};
int main(void)
{
	int i;
	i=0;
	DDRB=0xFF; //PB7-PB0 are programmed as outputs
	while ( 1 )
	{
		PORTB = LEDS[i];
		i++;
		i= i & 0x07;
		wait_milliseconds(500);
	}
	return 0;
}
*/
