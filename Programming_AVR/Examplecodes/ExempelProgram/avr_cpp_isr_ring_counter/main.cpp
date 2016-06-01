 /*
 * GccApplication1.cpp
 *
 * Created: 12/20/2013 12:05:19 PM
 *  Author: Kjell
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "io_bit_fields.h"
#include "ring_counter.h"

//Global i form av ett delat minne

volatile int g_key = 0;

//Visa hur adressen till denna läggs in i avbrottstabellen

ISR(INT0_vect)
{
	g_key++;
}

int main()
{
	ring_counter r(&PORTB);
	
	unsigned char stop=0;
	int key=0;
	int keyOld=0;

	bMCUCR.isc0 = 2; //Negative flanc
	bGICR.int0 = 1; //PD2
	asm(" SEI ");


	while ( 1 )
	{
		keyOld = key;

		asm("   CLI   ");
		key = g_key; //Atomär operation
		asm("   SEI   ");

		if ( key != keyOld )
		stop = !stop;

		if ( ! stop )
		{
			r.run();
			_delay_ms(300);
		}
	}

	return 0;
}
