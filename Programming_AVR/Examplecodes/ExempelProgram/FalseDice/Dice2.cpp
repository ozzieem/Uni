/*
* Dice2.cpp
*
* Created: 1/30/2015 1:54:16 PM
* Author: Kjell
*/


#include "Dice2.h"

// default constructor
Dice2::Dice2()
{
	this->state=Dice2::State::Normal;
	value = 1;
} //Dice2

void Dice2::Run(int eventThrow, int eventFalse)
{
	switch (this->state)
	{
		case State::Normal:
		//onEventThrow
		if (eventThrow)
		{
			Increment();
		}
		
		if (eventFalse)
		{
			state=State::False;
		}
		break;
		case State::False:
		if (eventThrow)
		{
			state = State::Throw1Active;
		}
		break;
		case State::Throw1Active:
		Increment();
		if (!eventThrow)
		{
			state = State::Throw1Finished;
			value=6;
		}
		break;
		case State::Throw1Finished:
		if (eventThrow)
		{
			state = State::Throw2Active;
		}
		break;
		case State::Throw2Active:
		Increment();
		if (!eventThrow)
		{
			state = State::Normal;
			value=6;
		}
		break;
		default:
		/* Your code here */
		break;
	}
}

void Dice2::Increment()
{
	//value = (this->value+1) > 6 ? value=1 : value++;
	value = value+1;
	if ( value > 6 )
		value = 1;
}

int Dice2::Value()
{
	return value;
}

// default destructor
Dice2::~Dice2()
{
} //~Dice2
