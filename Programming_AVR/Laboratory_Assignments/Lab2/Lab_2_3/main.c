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
		wait_milliseconds(500);
	}
}