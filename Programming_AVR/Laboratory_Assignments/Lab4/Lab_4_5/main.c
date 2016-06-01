#include <avr/io.h>
#include "lcd4.h"
#include "sensorSMT160.h"
#include "SMTLCD.h"

#define BIT7 0x80

int main(void)
{
	SMTLCD theDisplay;
	SensorSMT160 theTemperature;

	SMTLCD_init(&theDisplay);
	sensorSMT160_init(&theTemperature, &PINB, BIT7);

    while (1) 
    {
		sensorSMT160_read(&theTemperature);
		SMTLCD_display(&theDisplay, &theTemperature);
    }
}

