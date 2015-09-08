#include "dice.h";
#include <Windows.h>


void Dice::throw_dice()
{
	this->value = rand() % 6 + 1;
}

void Dice::read()
{
	cout << "Value of dice: " << this->value << endl;
}

void Dice::display_dice()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (this->value)
	{
	case 1:
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);

		cout << "|-------|\n"
				"|       |\n"
				"|   x   |\n"
				"|       |\n"
				"|-------|\n";
		break;

	case 2:
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "!-------!\n"
				"! x     !\n"
				"!       !\n"
				"!     x !\n"
				"!-------!\n";
		break;

	case 3:
		SetConsoleTextAttribute(h, FOREGROUND_RED);

		cout << "!-------!\n"
				"! x     !\n"
				"!   x   !\n"
				"!     x !\n"
				"!-------!\n";
		break;

	case 4:
		SetConsoleTextAttribute(h, 
			FOREGROUND_BLUE | FOREGROUND_GREEN); //Magenta

		cout << "!-------!\n"
				"! x   x !\n"
				"!       !\n"
				"! x   x !\n"
				"!-------!\n";
		break;

	case 5:
		SetConsoleTextAttribute(h, 
			FOREGROUND_GREEN | FOREGROUND_RED); //Yellow

		cout << "!-------!\n"
				"! x   x !\n"
				"!   x   !\n"
				"! x   x !\n"
				"!-------!\n";
		break;

	case 6:
		SetConsoleTextAttribute(h, 
			FOREGROUND_RED|FOREGROUND_BLUE); //Purple

		cout << "!-------!\n"
				"! x   x !\n"
				"! x   x !\n"
				"! x   x !\n"
				"!-------!\n";
		break;

	default:
		cerr << "!-------!\n"
				"!       !\n"
				"!       !\n"
				"!       !\n"
				"!-------!\n"
				"Something went wrong...\n";
		break;
	}
}