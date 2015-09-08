#pragma once

#include <iostream>
#include <string>

using namespace std;

class Multimedia
{

protected:
	string name;
	int year;

public:

	Multimedia(){name = ""; year = 0;}
	Multimedia(string n, int y){name = n; year = y;}

	virtual void add_item();
	virtual void display_item();
	
	//void setName(string n) { this->name = n; }
	//string getName() { return this->name; }

	~Multimedia() { cout << "Multimedia destructor"; }
};

//Methods
void Multimedia::add_item()
{
	cout << "Enter title: ";
	cin >> this->name;

	cout << "Enter year: ";
	cin >> this->year;
}

void Multimedia::display_item()
{
	cout << "Title: " << this->name << endl;
	cout << "Year: " << this->year << endl;
}

