
#include "dice.h"
#include <conio.h>

void printText()
{
	cout << "Welcome to Dice!\n"
		"To throw the dice press enter repeatedly.\n"
		"Press 'q' to quit!\n";
}

int main()
{

	Dice dice;

	printText();

	int c;
	while ((c = _getch()) != 'q')
	{
		system("cls"); //Använd helst inte system-funktioner...

		for (int i = 1; i <= 2; i++)
		{
			dice.throw_dice();
			dice.display_dice();
			dice.read();
			cout << endl;
		}
	}

	cout << "Shutting down..";

}