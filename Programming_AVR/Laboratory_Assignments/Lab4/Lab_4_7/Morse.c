#include "Morse.h"

const char morse_codes[10][6] =
{
	"_____", //0
	".____", //1
	"..___", //2
	"...__", //3
	"...._", //4
	".....", //5
	"_....", //6
	"__...", //7
	"___..", //8
	"____."  //9
};

morse_init(Morse* m)
{
	m->value = 0;
}

void morse_reset(Morse* m)
{
	for (int i=0; i<7; i++)
	{
		m->code[i]=' ';
	}
}

void morse_long(Morse* m, int code_count)
{
	m->code[code_count]='_';
}

void morse_short(Morse* m, int code_count)
{
	m->code[code_count]='.';
}

void morse_value(Morse* m)
{
	volatile int index = 0;

	for (int i = 0; i <= 10; i++)
	{
		m->code[5]=0;
		if(strcmp(morse_codes[i], m->code) == 0)
		{
			m->value = i; break;
		}
	}
}