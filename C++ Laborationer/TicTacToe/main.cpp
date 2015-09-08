#include "TicTacToe.h"


int main()
{
	Console::set_console_title("TicTacToe");

	TicTacToe game;

	char ch;

	while (true)
	{
		Console::clrscr();

		game.setup_board(game.board);

		//for (int i = 0; i < 10; i++) Använd för inputcheck
		//{
		ch = _getch();
		game.input_checker(ch);

		game.update_cursor_position();
		//}
	}

	_getch();
}
