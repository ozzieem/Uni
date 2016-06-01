#pragma once
#include "Counter.h"

Counter::Counter(){}

Counter::Counter(int min, int max)
{
	this->max = max;
	this->min = min;
	value = 0;
	lcd4_init(&this->lcd, &PORTB, &DDRB, 700, 50);
}

int Counter::Increment()
{
	if(value >= max)
	{
		value = min;
		return 1;
	}
	else
	{
		value++;
		return 0;
	}
}

int Counter::Decrement()
{
	value--;
	return 0;
}

int Counter::GetValue()
{
	return value;
}

void Counter::DisplayLCD()
{
	char s[20];
	sprintf(s, "Value: %d    ", this->value);
	lcd4_cup_row1(&this->lcd);
	lcd4_write_string(&this->lcd, s);
}