#pragma once

#include <time.h>
#include <iostream>
#include <Windows.h>

using namespace std;

class Dice
{
private:
	int value;

public:
	Dice()
	{
		srand(unsigned int(time(NULL)));
		value = 0;
	}

	void throw_dice();
	void display_dice();
	void read();
};