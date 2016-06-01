#include "Counter.h"

class Clock 
{
public:
	Counter hours, minutes, seconds;
	Clock();

	void UpdateClock();
};