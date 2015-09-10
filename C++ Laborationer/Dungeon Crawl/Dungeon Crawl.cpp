#include "Dungeon Crawl.h"


//Constructor
DungeonCrawl::DungeonCrawl()
{
	srand(unsigned int(time(NULL)));

	this->player.x = 2;
	this->player.y = 3;
	this->goal.x = 8;
	this->goal.y = 7;
}

void DungeonCrawl::playerMove()
{
	char c;
	board[this->player.y][this->player.x] = '-';

	switch (c = _getch())
	{
	case 'H':	//arrow up
		this->player.y -= 1;
		break;
	case 'P':	//arrow down
		this->player.y += 1;
		break;
	case 'M':	//arrow right
		this->player.x += 1;
		break;
	case 'K':	// arrow left
		this->player.x -= 1;
		break;
	default:
		break;

	}
}

void DungeonCrawl::drawMap()
{
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			cout << this->board[row][col];
		}
		cout << endl;
	}
}

void DungeonCrawl::createTraps()
{
		this->trap.x = rand() % 10;
		this->trap.y = rand() % 10;
}

void DungeonCrawl::placeTraps()
{
	for (int i = 0; i < 5; i++)
	{
		createTraps();
		this->board[this->trap.y][this->trap.x] = 'T';
	}
}

void DungeonCrawl::placePlayer()
{
	this->board[this->player.y][this->player.x] = 'P';
}

void DungeonCrawl::placeGoal()
{
	this->board[this->goal.y][this->goal.x] = 'X';
}

void DungeonCrawl::createMap()
{

	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			this->board[row][col] = '-';
		}
	}
}

void DungeonCrawl::checkPosition()
{
	Console::gotoxy(0, 12);

	if (this->board[this->player.y][this->player.x] == \
		this->board[this->goal.y][this->goal.x])
	{
		cout << "You did it!";
		cin.get();
	}
	else if (this->board[this->player.y][this->player.x] == \
		this->board[this->trap.y][this->trap.x])
	{
		cout << "You fell into a trap!";
		cin.get();
	}
}
