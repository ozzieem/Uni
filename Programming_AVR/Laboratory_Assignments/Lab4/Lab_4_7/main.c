#include <avr/io.h>
#include "MorseLCD.h"
#include "Morse.h"
#include "time.h"

void wait_milliseconds(int);

int main(void)
{
	MorseLCD morseLcd;
	morseLCD_init(&morseLcd);

	Morse morse;
	morse_init(&morse);
	morse_reset(&morse);

	char code_count = 0;

	unsigned tick_counter = 0;
	const unsigned tick = 10;
	unsigned reset_counter = 0;
	const unsigned reset_morse = 20;

	char const access_code = 5;		// Passcode
	char attempted_codes[6];
	const int lock_timeout = 20;
	int timeout_counter = 0;
	LockState = LOCKED;

	while (1)
	{
		
		// Buttons
		char button = (!(PINA & 0x01));
		switch ( ButtonState )
		{
			case IDLE:
			{
				tick_counter = 0;
				reset_counter++;
				if(button)
				{
					ButtonState = PUSHED;
					reset_counter = 0;
				}
			} break;
			
			case PUSHED:
			{
				tick_counter++;
				if(!button)
				{
					if(tick_counter < tick)
					{
						morse_short(&morse, code_count);
					}
					if(tick_counter > tick)
					{
						morse_long(&morse, code_count);
					}
					code_count++;

					ButtonState = IDLE;
				}
			} break;
		} // switch(ButtonState)


		// Kodlås
		switch(LockState)
		{
			case LOCKED:
			{
				morse_value(&morse);
				attempted_codes[code_count] = morse.value;
				if(code_count == 5 &&
				attempted_codes[code_count] == access_code)
				{
					LockState = UNLOCKED;
				}

				morseLCD_displaylock(&morseLcd, &morse, 0);
			} break;

			case UNLOCKED:
			{
				if(timeout_counter > lock_timeout)
				{
					LockState = LOCKED;
					timeout_counter = 0;
					code_count = 0;
				}
				timeout_counter++;
				morseLCD_displaylock(&morseLcd, &morse, 1);
			} break;
		} //switch(LockState)

		// Resets LCD-display after 20 ticks
		if (code_count == 5 || reset_counter > reset_morse)
		{
			code_count = 0;
			wait_milliseconds(1000);
			morse_reset(&morse);
		}
	}


}