#include "Byr�kraten.h"


int main()
{
	locale swedish("swedish");
	locale::global(swedish);

	cout << "V�lkommen till Byr�kraten!\n"
		"Tryck p� RETUR f�r meningar.\n"
		"Tryck 'q' f�r att avsluta!\n";

	int c;
	while ((c = _getch()) != 'q')
	{
		Console::clrscr();

		Byr�kraten sentence;

		//DEBUG
		//sentence.test_print();

		sentence.random_word();
		sentence.print_sentence();
	}

	cout << "Avslutar...";
}



