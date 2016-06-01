#include "MorseLCD.h"
#include "Morse.h"

void morseLCD_init(MorseLCD* mlcd)
{
	lcd4_init(&mlcd->lcdDisplay, &PORTB, &DDRB, 700, 50);
}

void morseLCD_display(MorseLCD* mlcd, Morse* m)
{
	m->code[7] = 0;
	
	sprintf(mlcd->s, "Morse: %s", m->code);
	lcd4_cup_row1(&mlcd->lcdDisplay);
	lcd4_write_string(&mlcd->lcdDisplay, mlcd->s);

	sprintf(mlcd->s, "Value: %d", m->value);
	lcd4_cup_row2(&mlcd->lcdDisplay);
	lcd4_write_string(&mlcd->lcdDisplay, mlcd->s);
}

void morseLCD_displaylock(MorseLCD* mlcd, Morse* m, int locked)
{

	m->code[7] = 0;
	sprintf(mlcd->s, "Morse: %s", m->code);
	lcd4_cup_row1(&mlcd->lcdDisplay);
	lcd4_write_string(&mlcd->lcdDisplay, mlcd->s);

	char *s;
	if(locked)
	{
		s = "UNLOCKED";
	}
	else
	{
		s = "LOCKED  ";
	}

	char buf[1024];
	memset(buf,0,sizeof buf);
	strncpy(buf,s,(sizeof buf)-1);

	sprintf(mlcd->s, "%s", s);
	lcd4_cup_row2(&mlcd->lcdDisplay);
	lcd4_write_string(&mlcd->lcdDisplay, s);
}