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

	Multimedia();
	Multimedia(string, int);

	virtual void add_item();
	virtual void display_item();
	
	//void setName(string n) { this->name = n; }
	//string getName() { return this->name; }

	~Multimedia() { cout << "Multimedia destructor"; }
};

