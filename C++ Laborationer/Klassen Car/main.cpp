#include "Car.h"

int main()
{

	Car bil1("Volvo", 2005, 97233.32);
	cout << "Initiliazed values: " << endl;
	bil1.display_values();

	char u_choice;

	cout << endl << "Would you like to enter your own values? (y/n)";
	cin >> u_choice;

	while (true)
	{
		if (u_choice == 'y' || u_choice == 'Y') {
			Car bil2;
			bil2.user_values();

			cout << endl << "Entered values: " << endl;
			bil2.display_values();

			cout << endl << "Try again? (y/n)";
			cin >> u_choice;
		}

		else
			break;
	}


	cout << "Shutting down...";

}