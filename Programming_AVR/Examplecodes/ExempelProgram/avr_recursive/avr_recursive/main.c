#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

char RFac(char n);

volatile int x;

int main()
{

	printf("Recursive functions and GCC for AVR\n\r");

	x = RFac(5);
	printf("5!=%d", x );

	return 0;
}
