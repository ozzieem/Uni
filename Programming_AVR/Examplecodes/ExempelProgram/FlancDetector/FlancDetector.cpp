/*
 * FlancDetector.cpp
 *
 * Created: 1/31/2015 6:10:26 AM
 *  Author: Kjell
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "io_bit_fields.h"

int sw0_negative_flanc_detector();

int main(void)
{
	bDDRB.D0 = 1;
	
    while(1)
    {
		if ( sw0_negative_flanc_detector() )
			bPORTB.D0 = !bPORTB.D0;
		_delay_ms(100);
    }
}