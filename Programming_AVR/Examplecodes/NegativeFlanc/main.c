#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void init_func();
void loop_func();
void wait_milliseconds(int milliseconds);
 
int dummy = 0x1234; //BUGG 

#include <avr/io.h>


int main(void)
{
    init_func();
	
    while (1) 
    {
		loop_func();
		//_delay_ms(50);
    }
}

