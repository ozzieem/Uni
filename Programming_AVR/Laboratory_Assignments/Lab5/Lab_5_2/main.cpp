#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd4.h"
#include "Counter.h"
#include "ClockLCD.h"
#include "Clock.h"

Clock clock;
Counter tick(0, 30);	// 30 Overflows ~= 1 second

ISR(TIMER0_OVF_vect)	// Interrupts when Timer has encountered overflow
{
	if(tick.Increment())	// Returns 1 if tick has reached 30
	{
		clock.UpdateClock();
	}
}

int main(void)
{
	ClockLCD lcd;

	TCCR0|=(1<<CS02)|(1<<CS00);
	// 8000000/1024 = 7812.5 Hz
	// Counting to 255 will take 7812.5 / 255 = 30.6...
	// One second takes ~30 overflows

	TIMSK|=(1<<TOIE0);	//Enable Overflow Interrupt
	TCNT0=0;			//Initialize Counter

	sei();

	while (1)
	{
		asm("CLI");
		lcd.DisplayClock(
		clock.hours.GetValue(),
		clock.minutes.GetValue(),
		clock.seconds.GetValue()
		);
		asm("SEI");
	}
}