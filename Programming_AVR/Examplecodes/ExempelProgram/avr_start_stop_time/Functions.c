/*
 * Functions.c
 *
 * Created: 1/24/2012 8:04:44 PM
 *  Author: kmo
 */ 

#include <avr/io.h>

volatile unsigned char counter_c = 0;
volatile unsigned char toggle_c = 0;
volatile unsigned char oldSW7_c = 0;


void sw7run_c()
{
		volatile unsigned char newSW7 = (PINA & 0x80) != 0;
		
		if ( !newSW7 && oldSW7_c)
		{
			toggle_c = !toggle_c;
		}
}

volatile unsigned char a=0x12;
volatile unsigned char b=0x34;
//volatile signed char a=0x12;
//volatile signed char b=0x34;
volatile signed char max;

void test()
{
	if (a>b)
		max=a;
	else
		max=b;
}

