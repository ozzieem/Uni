/*
 * CPPFile1.cpp
 *
 * Created: 1/31/2015 6:13:35 AM
 *  Author: Kjell
 */ 

#include "io_bit_fields.h"

enum class StateZO
{
	Start,
	Zero,
	One	
};

int sw0_negative_flanc_detector()
{
	static StateZO  state = StateZO::Start;
	
	switch( state )
	{
		
		case StateZO::Start:
			state = bPINA.D0 ? StateZO::One : StateZO::Zero;
			return 0;
		case StateZO::Zero:
			if ( bPINA.D0 )
			{
				state = StateZO::One;
			}
			return 0;
		case StateZO::One:
			if ( !bPINA.D0 )
			{
				state = StateZO::Zero;
				return 1;
			}
			return 0;
	}
	
	return 0;
}
