#include "Dice.h"

#define DICE_MAX 6

void dice_init(Dice* d)
{
	d->value = 0;
}

void dice_throw(Dice* d)
{
	d->value = rand() % DICE_MAX + 1;
}

int dice_value(Dice* d)
{
	return d->value;
}