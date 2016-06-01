#include "pattern8.h"

pattern8_init(Pattern8* p)
{
	p->i = 0;
	p->johnson = 0;
	p->counter = 0;
}

pattern8_next(Pattern8* p)
{
	pattern8_init(&p);
	switch(patternState)
	{
		case Ring:
		patternState = Johnson;
		break;
		case Johnson:
		patternState = Counter;
		break;
		case Counter:
		patternState = Flash;
		break;
		case Flash:
		patternState = Ring;
		break;
	}
}

char pattern8_ring(Pattern8* p)
{
	char leds[8] = {0x01, 0x02, 0x04, 0x08,
	0x10, 0x20, 0x40, 0x80};

	p->i++;
	p->i = p->i & 0x07;
	return ~leds[p->i];
}

int pattern8_johnson(Pattern8* p)
{
	if(( p->johnson & 0x80) == 0)
		p->johnson=(p->johnson << 1) + 1;
	else
		p->johnson = p->johnson << 1;
	return p->johnson;
}

int pattern8_counter(Pattern8* p)
{
	p->i++;
	return p->i;	
}

int pattern8_flashing(Pattern8* p)
{
	if(p->i < 255)
		p->i = p->i << 2;
	else if(p->i > 255)
		p->i = p->i >> 4;
	return p->i;
}