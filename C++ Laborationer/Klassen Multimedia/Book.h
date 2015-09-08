#pragma once

#include "Multimedia.h"

//Book
class Book :public Multimedia
{

private:
	string author;

public:
	void add_item();
	void display_item();

};

//Methods
void Book::add_item()
{

	Multimedia::add_item();

	cout << "Enter author: ";
	cin >> this->author;
}

void Book::display_item()
{
	Multimedia::display_item();

	cout << "Author: " << this->author << endl;
}