
#include "udelay.h"

/**
 *  Init of TIMER0 as a micro second counter, CPU clock is assumed to be 8MHz
 */
void udelay_timer0_init_8mhz()
{
	bTCCR0.cs0=2; //CK/8
}

/**
 * Micro second delay, maximum delay is 255 micro seconds
 */
 void udelay_timer0_delay(unsigned char del )
 {
	unsigned char start,stop;
	//del--;
	start = TCNT0;
	stop  = start + del;

	while ( stop != TCNT0 )
		;

 }
