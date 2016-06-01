#include <avr/io.h>


void init_func();
void loop_func();
void wait_milliseconds(int milliseconds);


int main(void)
{
	init_func();
	
	while (1)
	{
		loop_func();
	}
}