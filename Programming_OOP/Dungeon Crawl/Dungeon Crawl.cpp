#include "Dungeon Crawl.h"


//Constructor
DungeonCrawl::DungeonCrawl()
{
	srand(unsigned int(time(NULL)));

	this->maxBoard.row = 10;
	this->maxBoard.col = 10;
	this->active = true;
	this->mainloop = true;
	this->player.x = 2;
	this->player.y = 2;
	this->nTraps = (maxBoard.row + maxBoard.col) / 2;
	this->goal.x = maxBoard.row - 2;
	this->goal.y = maxBoard.col - 3;
}

DungeonCrawl::DungeonCrawl(int row, int col)
{
	srand(unsigned int(time(NULL)));

	this->maxBoard.row = row;
	this->maxBoard.col = col;
	this->active = true;
	this->mainloop = true;
	this->player.x = 2;
	this->player.y = 2;
	this->nTraps = (maxBoard.row + maxBoard.col) / 2;
	this->goal.x = maxBoard.row - 2;
	this->goal.y = maxBoard.col - 3;
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


void DungeonCrawl::createTraps()
{
		this->trap.x = rand() % maxBoard.row;
		this->trap.y = rand() % maxBoard.col;
}

void DungeonCrawl::placeTraps()
{
	for (int i = 0; i < nTraps; i++)
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

void DungeonCrawl::drawMap()
{
	for (int row = 0; row < maxBoard.row; row++)
	{
		for (int col = 0; col < maxBoard.col; col++)
		{
			cout << this->board[row][col];
		}
		cout << endl;
	}
}

void DungeonCrawl::createMap()
{

	for (int row = 0; row < maxBoard.row; row++)
	{
		for (int col = 0; col < maxBoard.col; col++)
		{
			this->board[row][col] = '-';
		}
	}
}

void DungeonCrawl::checkPosition()
{
	Console::gotoxy(0, maxBoard.col + 2);

	if (this->board[this->player.y][this->player.x] == this->board[this->goal.y][this->goal.x])
	{
		playerWon(true);
	}
	else if (this->board[this->player.y][this->player.x] == this->board[this->trap.y][this->trap.x])
	{
		playerWon(false);
	}
}

void DungeonCrawl::playerWon(bool state)
{
	if (state)
	{
		cout << "You did it!" << endl;
	}
	else
	{
		cout << "You fell into a trap!" << endl;
	}

	cout << "Restart game? (y/n)" << endl;
	char r;
	switch (r = _getch())
	{
	case 'y':
		this->active = false;
		this->mainloop = true;
		break;
	case 'n':
		this->active = false;
		this->mainloop = false;
		break;
	default:	//TODO: Can add some sort of wrong-input checker
		break; 
	}
}