#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io_bit_fields.h"
#include "MinKlass.h"
#include "ring_counter.h"

void wait_milliseconds(int); //Prototype

typedef struct
{
	unsigned char value;
	volatile unsigned char *port;
} ring;

void ring_init( ring *obj, volatile unsigned char *port )
{
	volatile unsigned char *ddr = port-1;
	obj->value=1;
	obj->port=port;

	*ddr = 0xFF;
	*(obj->port) = ~obj->value; //Ökar tydligheten, kompilatorn sköter optimeringen

}

void ring_run(ring *obj)
{
	obj->value = (obj->value << 1);
	if ( obj->value == 0)
		obj->value=1;

	*(obj->port) = ~obj->value;
}

//Global i form av ett delat minne

volatile int g_key = 0;

//Visa hur adressen till denna läggs in i avbrottstabellen

ISR(INT0_vect)
{
	g_key++;
}



int main()
{
	MinKlass obj;
	ring r;
	ring_counter r2(&PORTB);
	
	unsigned char stop=0;
	int key=0;
	int keyOld=0;

	ring_init(&r,&PORTB);

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
			ring_run(&r);
			//wait_milliseconds(500);		
		}
	}

	return 0;
}
