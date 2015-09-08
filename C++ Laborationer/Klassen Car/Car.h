#pragma once
#include <string>
#include <iostream>

using namespace std;

class Car {
public:
	string brand;
	int year;
	double price;

	Car(string b, int y, double p)
	{
		brand = b;
		year = y;
		price = p;
	}

	Car()
	{
		brand = "";
		year = 0;
		price = 0;
	}

	void display_values();
	void user_values();
};