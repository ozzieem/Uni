
#include <avr/io.h>
#include "ButtonMorse.h"
#include "lcd4.h"
#include "time.h"

time        theTime(time::MilliSecondsOne, time::TIMER2);
unsigned long long t;
unsigned long long T=50;

ButtonMorse bm(&PORTA,digital_input::D0, T);
lcd4        lcd(&PORTB,1000,100);



char codes[8];
char icodes=0;

ISR(TIMER2_COMP_vect)
{
	theTime.update();
}

int main(void)
{
	theTime.get(&t);
	asm(" sei ");
	while (1)
	{
		switch ( bm.read() )
		{
			case ButtonMorse::Input::Long:
			if ( icodes == 5)
			{
				icodes=0;
				for (int i=0; i<7; i++)
				{
					codes[i]=' ';
				}
			}
			codes[icodes++]='_';
			break;
			
			case ButtonMorse::Input::Short:
			if ( icodes == 5)
			{
				icodes=0;
				for (int i=0; i<7; i++)
				{
					codes[i]=' ';
				}
			}
			codes[icodes++]='.';
			break;
		}
		codes[7]=0;
		
		lcd.cup_row2();
		lcd.write_string(codes);
		
		t=t+T;
		theTime.wait_until(&t);
	}
}

