#pragma once
#include "lcd4.h"
#include "stdio.h"

class Counter
{
	int min, max;
	int value;
	lcd4 lcd;

public:
	Counter();
	Counter(int min, int max);
	
	int Increment();
	int Decrement();
	int GetValue();
	void DisplayLCD();
};