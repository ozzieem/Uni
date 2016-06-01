#ifndef MORSE_H_
#define MORSE_H_

#include <avr/io.h>

enum
{
	IDLE,
	PUSHED
} ButtonState;

enum
{
	UNLOCKED,
	LOCKED
} LockState;

typedef	struct  
{
	int value;
	char code[6];
} Morse;

void morse_init(Morse* m);
void morse_reset(Morse* m);
void morse_long(Morse* m, int);
void morse_short(Morse* m, int);
void morse_value(Morse* m);

#endif /* MORSE_H_ */