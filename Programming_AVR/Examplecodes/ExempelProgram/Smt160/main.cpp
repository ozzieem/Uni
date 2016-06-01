/*
 * Smt160.cpp
 *
 * Created: 2/10/2015 3:58:07 PM
 *  Author: Kjell
 */ 

#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"
#include "lcd4.h"
#include "smt160.h"

	lcd4	theLcd;

	//smt160  sensor1;
	//smt160  sensor1(1);
	//smt160  sensor1(smt160::MeasurementAlgorithm::SoftWareMultiplePeriods, &PIND, 0x40, 6);
	//smt160  sensor1(smt160::MeasurementAlgorithm::SoftwareOnePeriod, &PIND, 0x40, 6);
	//smt160  sensor1(smt160::MeasurementAlgorithm::HardwareTimer1, &PIND, 0x40, 6);
	smt160  sensor1(smt160::MeasurementAlgorithm::HardwareIsrTimer1Capture, &PIND, 0x40, 6);
	
	char s[20]; //Om du tar till för lite och överskrider spårar programmet ur

int main(void)
{
	lcd4_init(&theLcd,&PORTB,&DDRB,2000,100);	
	
	asm("    SEI   ");
				
    while(1)
    {		
		lcd4_cup_row1(&theLcd);
		lcd4_write_string(&theLcd, sensor1.get_temperature());
		
		lcd4_cup_row2(&theLcd);
		sprintf(s,"n=%5u o=%5u", sensor1.get_n(), sensor1.get_ones()); 
		lcd4_write_string(&theLcd, s);
		//lcd4_write_string(&theLcd, sensor1.get_str_isr_timer1_capture());
    }
}