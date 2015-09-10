#include "Dungeon Crawl.h"

int main()
{
	bool mainloop = true;

	while (mainloop)
	{
		DungeonCrawl game;
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

	cout << "Ending..." << endl;
	cin.get();
}