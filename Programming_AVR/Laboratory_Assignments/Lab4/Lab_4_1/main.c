#include <avr/io.h>
#include "pattern8.h"
#include "pulse.h"

void wait_milliseconds(int);

int main()
{
	Pulse p7;
	Pattern8 p8;

	while(1)
	{
		char sw7 = (!(PINA & 0x80));
		switch(patternState)
		{
			case Ring:
			{
				PORTB = pattern8_ring(&p8);
			} break;
			case Johnson:
			{
				PORTB = pattern8_johnson(&p8);
			} break;
			case Counter:
			{
				PORTB = pattern8_counter(&p8);
			} break;
			case Flash:
			{
				PORTB = pattern8_flashing(&p8);
			}
			default:
			{
			} break;
		} // switch

		// Move to next pattern
		if(pulse_run(&p7, sw7))
		{
			pattern8_next(&p8);
		}
		wait_milliseconds(100);
	}
}
