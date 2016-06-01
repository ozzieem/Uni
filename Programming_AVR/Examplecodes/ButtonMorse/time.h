#ifndef _H
#define _H

#include <stdio.h>
#include <avr/io.h>
//#include "io_usart.h"
#include "io_bit_fields.h"
#include <avr/interrupt.h>


class time
{
	public:
	enum Symbols
	{
		TIMER0,
		TIMER2,
		MilliSecondsTwo = 2,
		MilliSecondsOne = 1,
	};

	private:
	unsigned long long ms; //Absolute time
	unsigned char inc_ms;   //Each clock tick is on inc_ms
	
	private:
	void init_ocie0(void);
	void init_ocie2(void);
	
	public:

	time(unsigned char ms, unsigned char timer);
	void update(void);
	void get(unsigned long long *p_ms);
	void wait_until(unsigned long long *tWait);
	void wait_until2(unsigned long long tWait);
	void get_clock(int *h, int *m, int *s);
	void string(char *str);
	static unsigned long difference_ms(unsigned long long *tStart, unsigned long long *tEnd );
	static unsigned long difference_seconds(long long *tStart, long long *tEnd );

};

#endif
