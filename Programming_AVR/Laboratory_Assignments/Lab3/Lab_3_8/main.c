#include <avr/io.h>
#include <stdlib.h>
#include "..\..\help_files\Dice.h"

void wait_milliseconds(int);

enum { Normal, False } Dice;

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	
	int nFalseThrow = 0;
	int diceValue = 6;	// Inverted value for diode display

	bDicePORT.unusedOne = 1;
	bDicePORT.unusedTwo = 1;
	bDicePORT.diceTwo = diceValue;
	bDicePORT.diceOne = diceValue;

	Dice = Normal;

	while (1)
	{
		char NormalThrow = !(PINA & 0x01);
		char FalseThrow = !(PINA & 0x10);

		switch(Dice)
		{	
			case Normal:
			{
				if(NormalThrow)
				{
					if(diceValue >= 1)
					{
						bDicePORT.diceTwo = diceValue;
						bDicePORT.diceOne = diceValue;
						diceValue--;
						wait_milliseconds(200);
					}
					else
					{
						diceValue = 6;
					}
				}
				else if(FalseThrow)
				{
					Dice = False;
					nFalseThrow = 0;
				}
			} break;	// Normal
			case False:
			{
				if(NormalThrow)
				{
					diceValue = 1;
					if(nFalseThrow < 2)
					{
						bDicePORT.diceTwo = diceValue;
						bDicePORT.diceOne = diceValue;
						nFalseThrow++;
						wait_milliseconds(200);
					}
					else
					{
						diceValue = 6;
						bDicePORT.diceTwo = diceValue;
						bDicePORT.diceOne = diceValue;
						Dice = Normal;
						nFalseThrow = 0;
					}
				}
			} break;	//False
			default:
			break;
		}	// Switch
	}
}

