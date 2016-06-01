/*
 * FalseDice.cpp
 *
 * Created: 1/30/2015 1:51:19 PM
 *  Author: Kjell
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "io_bit_fields.h"
#include "Dice2.h"

int main(void)
{
	Dice2 dice;
	int eventThrow;
	int eventFalse;

	DDRB=0xFF;
		
    while(1)
    {
		eventThrow = !bPINA.D0;
		eventFalse = !bPINA.D7; 
		
		dice.Run(eventThrow,eventFalse);
		PORTB = ~dice.Value();
        _delay_ms(40); 
    }
}