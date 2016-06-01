#ifndef MORSELCD_H_
#define MORSELCD_H_

#include <util/delay.h>
#include "lcd4.h"
#include "Morse.h"

typedef struct
{
	char s[20];
	lcd4 lcdDisplay;
} MorseLCD;

void morseLCD_init(MorseLCD*);
void morseLCD_display(MorseLCD*, Morse* m);

#endif /* MORSELCD_H_ */