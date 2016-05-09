#include "Game.h"
#include "Player.h"

Game::Game game;
Player::Player p1(1, 1, 1);
Player::Player p2(2, 12, 12);

#pragma region UpdateFunctions
void UpdatePlayerOne()
{
	p1.Move();
}

void UpdatePlayerTwo()
{
	p2.Move();
}

void UpdateInput()
{
	while (true)
	{
		game.CheckInput(p1, p2);
	}
}
#pragma endregion

int main()
{
	Console::set_console_title("ThreadGame");

#if 1
	std::thread input_thread(UpdateInput);
	std::thread p1_thread(UpdatePlayerOne);
	std::thread p2_thread(UpdatePlayerTwo);
#endif

#if 0
	// Doesnt work properly with the movement
	thread input_thread(UpdateInput);
	thread p1_thread(p1);
	thread p2_thread(p2);
#endif

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		game.DrawBoard();
		game.DrawPlayer(p1, p2);
	}
}

