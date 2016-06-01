#include <avr/io.h>
#include <stdlib.h>
#include "Dice.h"

void wait_milliseconds(int);

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	
	bDicePORT.unusedOne = 1;
	bDicePORT.unusedTwo = 1;

	while (1)
	{
		int diceOneRandomValue = rand () % 6 + 1;
		int diceTwoRandomValue = rand () % 6 + 1;

		if(!(PINA & 0x08))
		{
			bDicePORT.diceOne = diceOneRandomValue;
			bDicePORT.diceTwo = diceTwoRandomValue;
		}
		wait_milliseconds(300);
	}
}

