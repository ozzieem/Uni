#include "Accelerator.h"

wait_milliseconds(int);

void accelerator_init(Accelerator* acc)
{
	DDRA = 0x00;
	countingState = IDLE;
	acc->value = 0;
	acc->counter = 0;
	acc->accelerationStart = 2;
}

void accelerator_increment(Accelerator* acc, char button)
{
	acc->value++;
	accelerator_delay(acc, button);
}

void accelerator_decrease(Accelerator* acc, char button)
{
	acc->value--;
	accelerator_delay(acc, button);
}

void accelerator_delay(Accelerator* acc, char button)
{
	if(button && acc->counter > acc->accelerationStart)
	{
		wait_milliseconds(100);
	}
	else if(button && acc->counter <= acc->accelerationStart)
	{
		wait_milliseconds(1000);
	}
	else
	{
		countingState = IDLE;
	}
	acc->counter++;
}


void accelerator_idle(Accelerator* acc,
char increaseButton, char decreaseButton)
{
	if(increaseButton)
	{
		countingState = INCREMENT;
	}
	else if(decreaseButton)
	{
		countingState = DECREASE;
	}
	acc->counter = 0;
}
