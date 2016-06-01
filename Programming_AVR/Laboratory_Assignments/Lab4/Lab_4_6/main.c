#include <avr/io.h>
#include "Accelerator.h"
#include "AccLCD.h"

char increasebutton_read();
char decreasebutton_read();

int main(void)
{
	AccLCD display;
	Accelerator acc;

	AccLCD_init(&display);
	accelerator_init(&acc);

	while (1)
	{
		char increaseButton = increasebutton_read();
		char decreaseButton = decreasebutton_read();
		switch(countingState)
		{
			case IDLE:
			{
				accelerator_idle(&acc, increaseButton, decreaseButton);
			} break;
			case INCREMENT:
			{
				accelerator_increment(&acc, increaseButton);
			} break;
			case DECREASE:
			{
				accelerator_decrease(&acc, decreaseButton);
			} break;
		}
		AccLCD_display(&display, &acc);
	}
}

char increasebutton_read()
{
	return (!(PINA & 0x01));
}

char decreasebutton_read()
{
	return (!(PINA & 0x02));
}