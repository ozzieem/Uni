#include "Dungeon Crawl.h"

int main()
{
	DungeonCrawl game;
	game.createMap();
	game.placeTraps();
	game.placeGoal();

	while (true)
	{
		Console::clrscr();
	
		game.placePlayer();	
		game.drawMap();
		game.playerMove();
		game.checkPosition();
		
	}

	cout << "test" << endl;
	cin.get();
}