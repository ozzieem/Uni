#include <avr/io.h>
#include <stdio.h>
#include "VoltLCD.h"
#include "Potentiometer.h"
#include "io_ai.h"

#define FIVE_VOLT_TIME 1000

int RingCounter(int, char*, Potentiometer);

int main(void)
{
	DDRD = 0xFF;
	io_ai InVolt;
	io_ai_init(&InVolt, IO_AI_CHANNEL0, 0);

	VoltLCD vLcd;
	Potentiometer potentioMeter;

	voltLCD_init(&vLcd);
	potentiometer_init(&potentioMeter);

	char leds[8] = 
	{0x01, 0x02, 0x04, 0x08,
	0x10, 0x20, 0x40, 0x80};
	int i = 0;

	while (1)
	{
		potentiometer_setvolts(&potentioMeter, io_ai_read(&InVolt));
		voltLCD_display(&vLcd, potentiometer_getvolts(&potentioMeter));

		i = RingCounter(i, leds, potentioMeter);
	}
}

int RingCounter(int i, char* leds, Potentiometer potentioMeter)
{
	i++;
	i = i & 0x07;
	PORTD = ~leds[i];

	int time = FIVE_VOLT_TIME - (potentiometer_getvolts(&potentioMeter) * 200);
	time = time > 0 ? wait_milliseconds(time) : wait_milliseconds(1);
	return i;
}
