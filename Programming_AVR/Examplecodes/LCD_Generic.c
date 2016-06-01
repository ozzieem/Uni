//Generic LCD C-code

#ifndef LCD_H_
#define LCD_H_

#include <util/delay.h>
#include "lcd4.h"
#include "Dice.h"

typedef struct
{
	char s[20];
	lcd4 lcdDisplay;
	
} LCD;

void InitDiceLCD(LCD*);
void DisplayLCD(LCD*, para1, para2);

#endif /* LCD_H_ */

____________________________________________________________

#include "LCD.h"

void InitLCD(LCD* dlcd)
{
	lcd4_init(&dlcd->lcdDisplay, &PORTB, &DDRB, 4000, 100);
}

void DisplayLCD(LCD* lcd, para1, para2)
{
	sprintf(dlcd->s, "Dice1 = %d", para1);
	lcd4_cup_row1(&dlcd->lcdDisplay);
	lcd4_write_string(&dlcd->lcdDisplay, dlcd->s);

	sprintf(dlcd->s, "Dice2 = %d", para2);
	lcd4_cup_row2(&dlcd->lcdDisplay);
	lcd4_write_string(&dlcd->lcdDisplay, dlcd->s);
}