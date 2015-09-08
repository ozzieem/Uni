#include "TicTacToe.h"

void TicTacToe::setup_board(char p[3][3])
{
	int rad, kol;
	char ram[7][14] = {
		"\332\304\304\304\302\304\304\304\302\304\304\304\277",
		"\263\040\040\040\263\040\040\040\263\040\040\040\263",
		"\303\304\304\304\305\304\304\304\305\304\304\304\264",
		"\263\040\040\040\263\040\040\040\263\040\040\040\263",
		"\303\304\304\304\305\304\304\304\305\304\304\304\264",
		"\263\040\040\040\263\040\040\040\263\040\040\040\263",
		"\300\304\304\304\301\304\304\304\301\304\304\304\331"
	};

	Console::clrscr();

	/* rita ram med övre vänstra hörnet på rad 10 kolumn 30 */
	for (rad = 0; rad <= 6; rad++) {
		Console::gotoxy(30, 10 + rad);
		for (kol = 0; kol <= 12; kol++)
			cout << ram[rad][kol];
	}

	Console::gotoxy(xcursor, ycursor);

	///* rita markeringarna */
	//for (rad = 0; rad < 3; rad++) {
	//	for (kol = 0; kol < 3; kol++) {
	//		Console::gotoxy(30 + 4 * kol + 2, 10 + 2 * rad + 1);
	//		if (p[rad][kol] == 'x')
	//			printf("%c", 'x');
	//		else if (p[rad][kol] == 'o')
	//			printf("%c", 'o');
	//	}
	//}
}


int TicTacToe::check_winner(char p[3][3])
{
	int count = 0;
	int row, column;

	// Checking 3 rows:
	for (row = 0; row < 3; ++row)
	{
		count = 0;
		for (column = 0; column < 3; ++column)
		{
			if (p[row][column] == 'x')
				count++;
			else if (p[row][column] == 'o')
				count--;
		}
		if (count == 3 || count == -3)
		{
			return abs(count / count); // Returns 1 
		}
	}

	// Checking 3 columns:
	for (column = 0; column < 3; ++column)
	{
		count = 0;
		for (row = 0; row < 3; ++row)
		{
			if (p[row][column] == 'x')
				count++;
			else if (p[row][column] == 'o')
				count--;
		}
		if (count == 3 || count == -3)
		{
			return abs(count / count);
		}
	}

	// Checking diagonal downward from left to right:
	count = 0;
	for (column = 0; column < 3; ++column)
	{
		if (p[column][column] == 'x')
			count++;
		else if (p[column][column] == 'o')
			count--;
	}
	if (count == 3 || count == -3)
	{
		return abs(count / count);
	}

	// Checking diagonal upward from left to right:
	count = 0;
	for (column = 0; column < 3; ++column)
	{
		if (p[column][2 - column] == 'x')
			count++;
		else if (p[column][2 - column] == 'o')
			count--;
	}
	if (count == 3 || count == -3)
	{
		return abs(count / count);
	}

	return 0;	// If there's no return 1 from the above loops

}

void TicTacToe::announce_winner(int n)
{
	if (n == 1)
	{
		cout << "x is winner" << endl;
	}
	else if (n == -1)
	{
		cout << "o is winner" << endl;
	}
	else
		cout << "Tie!" << endl;
}

void TicTacToe::input_checker(char c)
{
	c = _getch();
	switch (c)
	{
	case 'H':	//arrow up
		Console::gotoxy(xcursor, ycursor - 2);
		break;
	case 'P':	//arrow down
		Console::gotoxy(xcursor, ycursor + 2);
		break;
	case 'M':	//arrow right
		Console::gotoxy(xcursor + 4, ycursor);
		break;
	case 'K':	// arrow left
		Console::gotoxy(xcursor - 4, ycursor);
		break;
	default:
		break;

	}

}

void TicTacToe::update_cursor_position()
{
	this->xcursor = Console::wherex();
	this->ycursor = Console::wherey();
}