#include "Car.h"

void Car::display_values()
{
	cout << "Brand: " << brand << endl;
	cout << "Year: " << year << endl;
	cout << "Price: " << price << endl;
}

void Car::user_values()
{

	cout << "Enter brand: ";
	cin >> brand;

	cout << "Enter year: ";
	cin >> year;

	cout << "Enter price: ";
	cin >> price;

}