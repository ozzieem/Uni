#include <avr/io.h>

void wait_millseconds(int milliseconds);

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;

	char leds[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	unsigned char new_sw3, old_sw3, run;
	int i = 0;

	new_sw3 = old_sw3 = run = 1;

	while (1)
	{
		// switch
		old_sw3 = new_sw3;
		new_sw3 = (PINA & 0x08) == 0;
		if (old_sw3 && !new_sw3)
		{
			run = !run;
		}

		if(run)
		{
				PORTB = ~leds[i];
				i++;
				i = i & 0x07;
		}
		else
		{
			PORTB = 0xFF; //Släcka diod vid !run
		}

		wait_milliseconds(100);

	}
}
