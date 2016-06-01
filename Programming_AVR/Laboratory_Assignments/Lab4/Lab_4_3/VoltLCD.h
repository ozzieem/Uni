#ifndef VOLTLCD_H_
#define VOLTLCD_H_

#include <util/delay.h>
#include "lcd4.h"

typedef struct 
{
	char s[20];
	lcd4 lcdDisplay;
} VoltLCD;

void voltLCD_init(VoltLCD*);
void voltLCD_display(VoltLCD*, long);

#endif /* VOLTLCD_H_ */