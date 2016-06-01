#pragma once
#include "lcd4.h"
#include "stdio.h"

class ClockLCD
{
	lcd4 lcd;

	public:
	ClockLCD();

	void DisplayClock(int hours, int minutes, int seconds);
};