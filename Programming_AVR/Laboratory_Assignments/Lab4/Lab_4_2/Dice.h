#ifndef DICE_H_
#define DICE_H_

#include <stdlib.h>

typedef struct {
	int value;
} Dice;

void dice_init(Dice*);
int dice_value(Dice*);
void dice_throw(Dice*);

#endif /* DICE_H_ */