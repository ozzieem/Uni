#pragma once
#include "Player.h"
#include "Globals.h"

namespace Game
{
	class Game
	{
		char Tile = char(177);

		void operator()(Player::Player& p1, Player::Player& p2) const
		{
			while (true)
			{
				DrawBoard();
				DrawPlayer(p1, p2);
			}
		}

	public:
		/// Draws the gameboard
		void DrawBoard() const
		{
			Console::clrscr();
			Console::gotoxy(0, 0);
			for (auto row = 0; row < maxBoard.x_block; row++)
			{
				for (auto col = 0; col < maxBoard.y_block; col++)
				{
					std::cout << Tile;
				}
				Console::gotoxy(0, row);
			}
		}

		/// Draws player-position on board
		static void DrawPlayer(Player::Player& p1, Player::Player& p2)
		{
			Console::gotoxy(p1.GetX(), p1.GetY()); std::cout << p1.id;
			Console::gotoxy(p2.GetX(), p2.GetY()); std::cout << p2.id;
		}

		/// Checks input from Console
		static void CheckInput(Player::Player& p1, Player::Player& p2)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			mu.lock();	// lock_guard<mutex> guard(mu);
			if (_kbhit())
			{
				//TODO: Can be made dynamic if each player owns the assigned keys
				auto c = _getch();
				if (c == 'i' || c == 'j' || c == 'k' || c == 'l')
				{
					p2.dKeys.push_front(c);
				}
				else if (c == 'w' || c == 'a' || c == 's' || c == 'd')
				{
					p1.dKeys.push_front(c);
				}
			}
			mu.unlock(); // Remove if lock_guard is used
		}
	};
}
