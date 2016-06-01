#include "sensorSMT160.h"

void sensorSMT160_init(SensorSMT160* smt, char* pin, char bit_mask)
{
	smt->pin = pin;
	smt->bit_mask = bit_mask;
	smt->value = 0;
}

float sensorSMT160_read(SensorSMT160* smt)
{
	unsigned int n = 50000;
	unsigned int ones = sensor_smt160_sample(smt->pin, smt->bit_mask, n);
	float dc = (float) ones / (float) n;
	float temp = (dc - 0.32) / 0.00470;

	smt->value =  temp;
	return temp;
}

__attribute__((noinline))
unsigned int sensor_smt160_sample(
volatile unsigned char* pin, //Register R25:R24
unsigned char bit_mask, //Register R22
unsigned int n //Register R21:R20
)
{
	asm volatile (
	" movw r30, r24 " "\n\t"
	" movw r26, r20 " "\n\t"
	" ldi r24, 0x00 " "\n\t"
	" ldi r25, 0x00 " "\n\t"
	" ldi r19, 0xff " "\n\t"
	" ldi r20, 0x00 " "\n\t"
	"loop: " "\n\t"
	" ld r18, Z " "\n\t"
	" and r18, r22 " "\n\t"
	" add r18, r19 " "\n\t"
	" adc r24, r20 " "\n\t"
	" adc r25, r20 " "\n\t"
	" sbiw r26, 0x01 " "\n\t"
	" brne loop " "\n\t"
	" ret " "\n\t"
	);
}

void sensorSMT160_testSignalChange()
{
	/* Test that there's a sensorsignal on the digital input.
	If signal is constant for a period of time ie 10 ms,
	then its something wrong on the sensor */
}

void sensorSMT160_testSignalFrequency()
{
	/* The frequency on the signal from the sensor shall be in the
	interval of 1-4 kHz. If it's not then there's probably sensorfault.
	Tests if the frequency on the sensorsignal is in a given interval. */
}