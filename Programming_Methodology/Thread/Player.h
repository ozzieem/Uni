#pragma once
#include "Game.h"
#include <deque>
#include "Globals.h"

namespace Player
{
	class Player
	{
	public:
		std::deque<char> dKeys;
		Position position;
		int id;

		void operator()()
		{
			Move();
		}

		Player()
		{
			this->id = 0;
			this->position = Position();
		}

		Player(int id, int startX, int startY)
		{
			this->id = id;
			this->position = Position(startX, startY);
		}

		/// Checking for player-input
		void Move()
		{
			while (true)
			{
				std::lock_guard<std::mutex> guard(mu);
				if (!dKeys.empty())
				{
					if (this->id == 1)
					{
						CheckKeys(dKeys.back(), 'w', 'a', 's', 'd');
					}
					else if (this->id == 2)
					{
						CheckKeys(dKeys.back(), 'i', 'j', 'k', 'l');
					}
					CheckBoundary();
					dKeys.pop_back();
				}
			}
		}

		/// Decides action for each key
		void CheckKeys(char key, char up, char right, char down, char left)
		{
			if (key == up)
			{
				position.y--;
			}
			if (key == right)
			{
				position.x--;
			}
			if (key == down)
			{
				position.y++;
			}
			if (key == left)
			{
				position.x++;
			}
		}

		/// Checks player position to board boundaries
		void CheckBoundary()
		{
			if (position.x < 0)
			{
				position.x += 1;
			}
			if (position.y < 0)
			{
				position.y += 1;
			}
			if (position.x >= maxBoard.x_block)
			{
				position.x -= 1;
			}
			if (position.y >= maxBoard.y_block - 1)
			{
				position.y -= 1;
			}
		}

#pragma region Getters
		int GetX() const
		{
			return position.x;
		}

		int GetY() const
		{
			return position.y;
		}
#pragma endregion
	};
}
