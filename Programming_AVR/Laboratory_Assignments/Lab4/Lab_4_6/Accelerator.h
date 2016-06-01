#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_
#include <avr/io.h>

enum Counting {
	INCREMENT,
	DECREASE,
	IDLE
} countingState;

typedef struct  
{
	int value;
	int counter;
	int accelerationStart;
	unsigned char button;
} Accelerator;

void accelerator_init(Accelerator*);
void accelerator_increment(Accelerator*, char);
void accelerator_decrease(Accelerator*, char);
void accelerator_delay(Accelerator*, char);
void accelerator_idle(Accelerator*, char, char);

#endif /* ACCELERATOR_H_ */