#include <avr/io.h>


void init_func();
void loop_func();
void wait_milliseconds(int milliseconds);


int main(void)
{
	init_func();
	
	while (1)
	{
		loop_func();
		//wait_milliseconds(500);
		
		/*
				R20 = PINA & 0x08;
				R20 = R20 >> 3;
				R21 = PORTB & 0xFE;
				R20 = R20 | R21;
				PORTB = R20;
		*/
	}
}