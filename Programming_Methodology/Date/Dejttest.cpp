#include <iostream>
#include <istream>

#include "Dating.h"

using std::string;

int main()
{
	while (true)
	{
		Dating dating;

		int input;
		cout << "1. List all people\n"
			<< "2. List all females\n"
			<< "3. List all males\n"
			<< "4. Match available people\n" << endl;
		std::cin >> input;

		switch (input)
		{
		case 1:
			dating.DisplayAllLists();
			break;
		case 2:
			dating.DisplayFemales();
			break;
		case 3:
			dating.DisplayMales();
			break;
		case 4:
			dating.matchCouples();
			break;
		default:
			cout << "Try again" << endl;
			break;
		}
	}
}

