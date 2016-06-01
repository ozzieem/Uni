#include <avr/io.h>

static int n = 0;
static enum {Zero, Wait, One} Signal;

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0x00;
	Signal = Zero;

	while (1)
	{
		char input = !(PINA & 0x01);
		PORTB = 255 - bounce(input);
		wait_milliseconds(100);
	}
}

int bounce(int signal)
{
	switch (Signal)
	{
		case Zero:
		{
			if(signal == 1)
			{
				Signal = One;
			}
			return 0;
		} break;
		case One:
		{
			if(signal == 0)
			{
				Signal = Wait;
				n = 10;
				return 1;
			}
			return 0;
		} break;
		case Wait:
		{
			n--;
			if(n == 0)
			{
				Signal = Zero;
				return 0;
			}
		} break;
		default:
		break;
	}
}
