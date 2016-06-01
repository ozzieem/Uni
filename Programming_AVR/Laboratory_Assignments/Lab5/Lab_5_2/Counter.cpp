#pragma once
#include "Counter.h"

Counter::Counter(){}

Counter::Counter(int min, int max)
{
	this->max = max;
	this->min = min;
	value = 0;
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

int Counter::GetMax()
{
	return max;
}