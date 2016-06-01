#include <avr/io.h>


void init_func();
void loop_func();
void wait_milliseconds(int milliseconds);

int dummy = 0x1234;

int main(void)
{
	init_func();
	
	while (1)
	{
		loop_func();
		wait_milliseconds(150);
	}
}

int main()
{

	DDRB = 0xFF;
	DDRA = 0x00;
	newValue = PINA & 0x01;
	oldValue = newValue;

	int counter = 0;
	
	while(true)
	{

		oldValue = newValue;
		newValue = PINA & 0x01;

		if(oldValue != newValue)
		counter++;

		PORTB = counter;
	}

}