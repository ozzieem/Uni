#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include "Console.h"

using namespace std;
using namespace Course;

class DungeonCrawl
{

private: 

	string board[10][10];

	struct Position
	{
		int x;
		int y;
	};

	Position player, trap, goal;

public:
	DungeonCrawl();
	~DungeonCrawl() { cout << "Deconstruct"; }

	void checkPosition();
	void playerMove();
	void drawMap();
	void createTraps();
	void placeTraps();
	void placePlayer();
	void placeGoal();
	void createMap();
};
