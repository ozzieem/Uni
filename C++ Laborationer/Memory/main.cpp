#include "MemorySpace.h"

using namespace MemorySpace;

int main()
{
	Memory game;
	game.CreateCards();
	game.GenMemCards();

	while (true)
	{
		game.PrintCards();
		game.cardFlip();
		
		//Console::clrscr();
	}

	cin.get();

}