
#include <iostream>
#include "Kaprekar.h"

using namespace std;

//	KAPREKAR-MAIN


int main()
{
	int uservalue, choice;

	printMenu();
	cin >> choice;

	system("cls");

	while (choice != 0)
	{
		int count = 0;

		if (choice == 1)
		{
			cout << "Enter a 4-digit integer (0 to quit): ";
			cin >> uservalue;
			if (uservalue == 0)
			{
				break;
			}
			else
			{
				cout << "Calculating";
				printDots();
				cout << endl;

				while (uservalue != 6174)
				{
					count++;
					uservalue = calc(uservalue);
					cout << endl;
				}

				cout << "It took " << count << " iterations to reach 6174!" << endl << endl;
				sleepFor(1000);
			}
		}

		else
		{
			ErrorMessage();

			printMenu();
			cin >> choice;
		}

	} //while

	system("cls");
	cout << "Shutting Down";
	printDots();
}