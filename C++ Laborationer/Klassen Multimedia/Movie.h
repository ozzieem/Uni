#pragma once

#include "Multimedia.h"

class Movie : public Multimedia
{

private:
	string producer;
public:

	Movie() { name = ""; year = 0; producer = ""; }

	void add_item();
	void display_item();

	//void setName(string n) { this->name = n; }
	//string getName() { return this->name; }

};

//Methods

void Movie::add_item()
{
	Multimedia::add_item();

	cout << "Enter producer: ";
	cin >> this->producer;
}

void Movie::display_item()
{
}
