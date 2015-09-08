#pragma once

#include <time.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class Dice
{
private:
	int value;

public:
	Dice()
	{
		srand(time(NULL));
		value = 0;
	}

	void throw_dice();
	void display_dice();
	void read();
};