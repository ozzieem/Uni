#include "sensorSMT160.h"
#include "SMTLCD.h"

void SMTLCD_init(SMTLCD* smtLcd)
{
	lcd4_init(&smtLcd->lcdDisplay, &PORTB, &DDRB, 4000, 100);
}

void SMTLCD_display(SMTLCD* smtLcd, SensorSMT160* smt)
{
	sprintf(smtLcd->s, "Temperature:");
	lcd4_cup_row1(&smtLcd->lcdDisplay);
	lcd4_write_string(&smtLcd->lcdDisplay, smtLcd->s);

	sprintf(smtLcd->s, "%d", smt->value);
	lcd4_cup_row2(&smtLcd->lcdDisplay);
	lcd4_write_string(&smtLcd->lcdDisplay, smtLcd->s);

	lcd4_write_char(&smtLcd->lcdDisplay, 0xDF);
	lcd4_write_char(&smtLcd->lcdDisplay, 'C');
}