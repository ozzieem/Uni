/*
* ButtonMorse.h
*
* Created: 3/2/2016 8:32:03 AM
* Author: kmo
*/


#ifndef __BUTTONMORSE_H__
#define __BUTTONMORSE_H__

#include <avr/io.h>
#include "di.h"
class ButtonMorse
{
	//variables
	public:
	enum class Input
	{
		None,
		Short,
		Long
	};
	
	enum class States
	{
		Idle,
		Pushed
	};
	
	protected:
	private:
	States _state = States::Idle;
	Input  _input = Input::None;
	digital_input _di;
	int _time=0;
	int _tick=0;
	int _time_long = 1000; //ms

	//functions
	public:
	__attribute__((noinline))
	ButtonMorse(volatile unsigned char *port, unsigned char bit_mask, int tick)
	: _di(port,bit_mask)
	{
		_di   = digital_input(port, bit_mask);
		_tick = tick;
	}
	
	
	__attribute__((noinline))
	Input read()
	{
		fsm();
		return _input;
	}
	
	protected:
	private:
	__attribute__((noinline))
	void fsm()
	{
		switch (_state)
		{
			case States::Idle:
			{
				_input=Input::None;
				if ( _di.read() == 0 )
				{
					_state=States::Pushed;
					_time = 0;
				}
			} break;
			case States::Pushed:
			{
				_time += _tick;
				if ( _di.read() == 1)
				{
					_state = States::Idle;
					if ( _time <  _time_long)
					{
						_input = Input::Short;
					}
					else
					{
						_input = Input::Long;
					}
				}
			} break;
		}
	}
}; //ButtonMorse

#endif //__BUTTONMORSE_H__
