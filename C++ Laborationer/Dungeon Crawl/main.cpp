#include "Dungeon Crawl.h"

void UserBoard(int &, int &);

int main()
{
	int TempRow;
	int TempCol;

	UserBoard(TempRow, TempCol);

	bool mainloop = true;

	while (mainloop)
	{
		DungeonCrawl game (TempRow, TempCol);
		game.createMap();
		game.placeTraps();
		game.placeGoal();

		while (game.active)
		{
			Console::clrscr();

			game.placePlayer();
			game.drawMap();
			game.playerMove();
			game.checkPosition();
		}

		if (!game.mainloop)
			mainloop = false;
	}

	cout << "Press ENTER to quit..." << endl;
	
	cin >> TempRow;	 //DEBUG
}


void UserBoard(int &row, int &col)
{
	cout << "Choose the size of your board:" << endl;
	cout << "Enter row and column (max: 30 30):";
	cin >> row >> col;
	cout << "\n Starting game...";
	Console::clrscr();
}