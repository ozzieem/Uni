#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"
#include "lcd4.h"
#include "wire3.h"

void wait_milliseconds(int); //Prototype

//===========================================================
//===test_ds1620=============================================
//===========================================================
void test_ds1620(void)
{
	int toggle=0;
	lcd4     theLCD;
	unsigned int temp=-1;
	char s[20];

	lcd4_init(&theLCD,&PORTD, &DDRD, 4000, 100);
	lcd4_cup_row1(&theLCD);
	lcd4_write_string(&theLCD, "DS1620-TEST");
	
	wire3_init(3);

	wire3_rst_1(0); //Enable communication
	wire3_write8(0x0C);  //0x0C
	wire3_write8(0x0A); //Normal CPU-communication
	wire3_rst_0(0); //Disable communication

	wire3_rst_1(0); //Enable communication
	wire3_write8(0xEE);  //0xEE
	wire3_rst_0(0); //Disable communication



	while (1)
	{
		//wire3_ds1620_temperature( 0, &temp);
		if ( (toggle = (! toggle)) )
			sprintf(s,"%3d %c%c  %c",temp, 0xDF, 'C', '.');
		else
			sprintf(s,"%3d %c%c  %c",temp, 0xDF, 'C', ' ');
		lcd4_cup_row2(&theLCD);
		lcd4_write_string(&theLCD, s);
	}
}



//===========================================================
//===main====================================================
//===========================================================
int main()
{

	test_ds1620();

	return 0;
}
