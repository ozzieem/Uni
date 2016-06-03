#include "Clock.h"

Clock::Clock()
{
	this->hours = Counter(0, 23);
	this->minutes = Counter(0, 59);
	this->seconds = Counter(0, 59);
}

void Clock::Update()
{
		if(this->seconds.GetValue() < this->seconds.GetMax())
		{
			this->seconds.Increment();
		}
		else if (this->minutes.GetValue() < this->minutes.GetMax())
		{
			this->seconds.Increment();	// reset
			this->minutes.Increment();
		}
		else if(this->hours.GetValue() <= this->hours.GetMax())
		{
			this->seconds.Increment();	// reset
			this->minutes.Increment();	// reset
			this->hours.Increment();
		}
}