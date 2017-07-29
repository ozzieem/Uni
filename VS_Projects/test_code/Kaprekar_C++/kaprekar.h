#ifndef __KAPREKAR_H_INCLUDED__
#define __KAPREKAR_H_INCLUDED__

#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

// KAPREKAR - FUNCTIONS


void sleepFor(int x)
{
	this_thread::sleep_for(chrono::milliseconds(x));
}

void printDots()
{
	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		sleepFor(0300);
	}
}

const int INTSIZE = 4;

int integersort(int uservalue, int mode)
{
	int values[INTSIZE];
	int temp = 0;

	//Putting int into array
	for (int i = 0; i < INTSIZE; i++)
	{
		values[i] = uservalue % 10;
		uservalue /= 10;
	}

	// 1 == Descending, 2 == Ascending
	if (mode == 1)
		sort(values, values + INTSIZE, greater<int>());
	else
		sort(values, values + INTSIZE);

	//Turning array into integer value
	int result = 0;

	for (int i = 0; i < INTSIZE; i++)
	{
		result *= 10;
		result += values[i];
	}

	return result;
}


int calc(int number)
{
	int min, max, result;

	//  2 == Ascending, 1 == Descending
	min = integersort(number, 2);
	max = integersort(number, 1);

	result = max - min;
	cout << max << " - " << min << " = " << result;

	return result;
}

void ErrorMessage()
{
	system("cls");
	cout << "Invalid entry. Try again." << endl;
	cin.clear(); // clears the error state
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear bad input buffer
	sleepFor(1000);
	system("cls");
}

void printMenu()
{
	cout << "Make your choice:\n"
			" 1. Enter an integer for Kaprekar's Constant\n"
			" 0. Quit\n"
			"Enter your choice: ";
}


#endif // __KAPREKAR_H_INCLUDED__