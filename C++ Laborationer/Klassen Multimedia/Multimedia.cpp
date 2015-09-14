#include "Multimedia.h"
#include "MultiMediaRegister.h"


Multimedia::Multimedia()
{
	name = ""; 
	year = 0;
}

Multimedia::Multimedia(string n, int y)
{
	name = n; 
	year = y;
}


void Multimedia::add_item()
{
	cout << "Enter title and year (with space inbetween): ";
	cin >> this->name >> this->year;
	MultimediaRegister::

}

void Multimedia::display_item()
{
	cout << "Title: " << this->name << " " 
		<< "Year: " << this->year << endl;
}