#include <avr/io.h>
#include <util/delay.h>
#include "LogicSignal.h"
#include "io_bit_fields.h"

extern "C" 
{ 
	void wait_milliseconds(int); 
};


int main(void)
{
    LogicSignal ls;
	DDRB=0xFF;
	
    while (1) 
    {
		ls.Run(bPINA.D0);
		
		bPORTB.D0= ! ls.Signal();
		bPORTB.D1= ! ls.NegativeFlanc();
		bPORTB.D2= ! ls.NegativeToggle();
		bPORTB.D3= ! ls.PositiveFlanc();
		bPORTB.D4= ! ls.PositiveToggle();
		bPORTB.D5= ! ls.Flanc();
		bPORTB.D6= ! ls.Toggle();
		bPORTB.D7= 1;
		
		wait_milliseconds(2000);
    }
}

