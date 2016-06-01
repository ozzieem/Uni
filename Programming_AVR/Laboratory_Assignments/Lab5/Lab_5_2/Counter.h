#pragma once
#include "stdio.h"

class Counter
{
	int min, max;
	int value;

public:
	Counter();
	Counter(int min, int max);
	
	int Increment();
	int Decrement();
	int GetValue();
	int GetMax();
};