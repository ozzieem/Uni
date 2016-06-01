#ifndef MORSEINPUT_H_
#define MORSEINPUT_H_

#include "MorseTime.h"
#include "Morse.h"

typedef struct
{
	char button;
} MorseInput;

morseInput_init(MorseInput*);
morseInput_run(MorseInput*, MorseTime*, Morse*, int*);



#endif /* MORSEINPUT_H_ */