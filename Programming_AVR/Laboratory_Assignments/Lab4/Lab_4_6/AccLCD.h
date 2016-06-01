#ifndef ACCLCD_H_
#define ACCLCD_H_

#include <util/delay.h>
#include "lcd4.h"
#include "Accelerator.h"

typedef struct
{
	char s[20];
	lcd4 lcdDisplay;
} AccLCD;

void AccLCD_init(AccLCD*);
void AccLCD_display(AccLCD*, Accelerator*);

#endif /* ACCLCD_H_ */