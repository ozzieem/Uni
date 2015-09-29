#include "MemorySpace.h"

using namespace MemorySpace;
using namespace Course;

int main()
{
	Memory game;
	HighScore highScore;
	game.CreateCards();
	game.GenMemCards();

	while (true)
	{

			Console::clrscr();
			game.PrintCards();
			game.CardNav();

	}

	highScore.writeFile();

	return 0;
}