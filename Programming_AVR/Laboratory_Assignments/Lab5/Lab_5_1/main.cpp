#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd4.h"
#include "Counter.h"

Counter counter(0, 10);

ISR(INT0_vect)
{
	counter.Increment();
}

int main(void)
{
	GICR = 1<<INT0;
	MCUCR = 1<<ISC01 | 1<<ISC00;
	sei();

	while (1)
	{
		asm("CLI");
		counter.DisplayLCD();
		asm("SEI");
		_delay_ms(2000);
	}
}

