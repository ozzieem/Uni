#ifndef PATTERN8_H_
#define PATTERN8_H_
#include "avr/io.h"

enum Pattern {
	Ring,
	Johnson,
	Counter,
	Flash
} patternState;

typedef struct {
	int i;
	int johnson;
	int counter;
} Pattern8;

void pattern8_init(Pattern8* p);
void pattern8_next(Pattern8* p);
void pattern8_run(Pattern8* p);

char pattern8_ring(Pattern8* p);
int pattern8_johnson(Pattern8* p);
int pattern8_counter(Pattern8* p);
int pattern8_flashing(Pattern8* p);

#define pattern (*(volatile Pattern8)* &PORTB)

#endif /* PATTERN8_H_ */