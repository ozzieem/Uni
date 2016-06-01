#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

int maxInt(int a, int b);
void minInt(int a, int b, int *min );

volatile int tal1=20;
volatile int tal2=30;
volatile int res =0;

int main()
{

	printf("Function parameters and GCC for AVR\n\r");

	 minInt(tal1, tal2, &res);	
	printf("Min number of %d and %d is %d\n\r", tal1, tal2, res);
	
	res = maxInt(tal1 , tal2 );
	printf("Max number of %d and %d is %d\n\r", tal1, tal2, res);
	

	return 0;
}
