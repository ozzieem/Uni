#ifndef SENSORSMT160_H_
#define SENSORSMT160_H_

#include <avr/io.h>

typedef struct 
{
	int value;
	unsigned char* pin;
	unsigned char bit_mask;
} SensorSMT160;

void sensorSMT160_init(SensorSMT160*, char*, char);
float sensorSMT160_read(SensorSMT160*);
unsigned int sensor_smt160_sample(volatile unsigned char* pin, 
									unsigned char bit_mask, 
										unsigned int);
void sensorSMT160_testSignalChange();
void sensorSMT160_testSignalFrequency();


#endif /* SENSORSMT160_H_ */