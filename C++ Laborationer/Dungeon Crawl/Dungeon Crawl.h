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
	~DungeonCrawl() { cout << "Deconstructing class\n"; }

	bool active;
	bool mainloop;

	void checkPosition();
	void drawMap();

	void playerWon(bool);
	void playerMove();

	void createTraps();
	void createMap();

	void placeTraps();
	void placePlayer();
	void placeGoal();
	
};
