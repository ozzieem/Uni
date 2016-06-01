#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

int dummy = 0x1234; //Behövs för att initierat data i assembler skall initieras, BUG i kompilatorn sen 2009

void init_func();
void loop_func();
void wait_milliseconds(int);
void test();

int main()
{
	test();

 	init_func();

	while ( 1 )
	{
		loop_func(); //Om vi kör i simulatorn glöm ej att ettställa PINA7 och PINA0 för att efterlikna STK500
		//wait_milliseconds(125);
	}

	return 0;
}
