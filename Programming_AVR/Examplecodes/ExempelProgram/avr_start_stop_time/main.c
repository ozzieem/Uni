#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

int dummy = 0x1234; //Beh�vs f�r att initierat data i assembler skall initieras, BUG i kompilatorn sen 2009

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
		loop_func(); //Om vi k�r i simulatorn gl�m ej att ettst�lla PINA7 och PINA0 f�r att efterlikna STK500
		//wait_milliseconds(125);
	}

	return 0;
}
