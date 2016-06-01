#ifndef SMTLCD_H_
#define SMTLCD_H_

#include <util/delay.h>
#include "lcd4.h"
#include "sensorSMT160.h"

typedef struct 
{
	char s[20];
	lcd4 lcdDisplay;
} SMTLCD;

void SMTLCD_init(SMTLCD*);
void SMTLCD_display(SMTLCD*, SensorSMT160*);

#endif /* SMTLCD_H_ */