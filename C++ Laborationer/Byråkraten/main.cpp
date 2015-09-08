#include "Byråkraten.h"


int main()
{
	locale swedish("swedish");
	locale::global(swedish);

	cout << "Välkommen till Byråkraten!\n"
		"Tryck på RETUR för meningar.\n"
		"Tryck 'q' för att avsluta!\n";

	int c;
	while ((c = _getch()) != 'q')
	{
		Console::clrscr();

		Byråkraten sentence;

		//DEBUG
		//sentence.test_print();

		sentence.random_word();
		sentence.print_sentence();
	}

	cout << "Avslutar...";
}



