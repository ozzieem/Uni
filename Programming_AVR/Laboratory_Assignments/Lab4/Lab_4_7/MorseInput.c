#include "MorseInput.h"

morseInput_init(MorseInput* mi)
{
	ButtonState = IDLE;
}

morseInput_run(MorseInput* mi, MorseTime *mt, Morse* m, int* code_count)
{
		mi->button = (!(PINA & 0x01));
		switch ( ButtonState )
		{
			case IDLE:
			{
				mt->tick_counter = 0;
				mt->reset_counter++;
				if(mi->button)
				{
					ButtonState = PUSHED;
					mt->reset_counter = 0;
				}
			} break;
			
			case PUSHED:
			{
				mt->tick_counter++;
				if(!mi->button)
				{
					if(mt->tick_counter < mt->tick)
					{
						morse_short(&m, code_count);
					}
					if(mt->tick_counter > mt->tick)
					{
						morse_long(&m, code_count);
					}
					(*code_count)++;

					ButtonState = IDLE;
				}
			} break;
		} // switch(ButtonState)
}
