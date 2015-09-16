#pragma once

#include "VectorFloat.h"

// Konstruktor
VectorFloat::VectorFloat()
{
	VectorFloat::CreateVector(0);
}

VectorFloat::VectorFloat(int s)
{
	VectorFloat::CreateVector(s);
}

//Destruktor
VectorFloat::~VectorFloat()
{
	DeleteVector();
}


void VectorFloat::CreateVector(int s)
{
	this->vptr = new vector<float>(s);
	this->size = s;
}	

void VectorFloat::DeleteVector()
{
	delete this->vptr;
	this->size = 0;
}

void VectorFloat::Set(float value, int index)
{
	try
	{
		if (index < 0 || index > this->vptr->size())
		{
			throw "index is less than 0 or out of bound";
		}
	}
	catch (bad_typeid)
	{
		cerr << "Not correct type";
	}
	
	this->vptr->at(index) = value - 48; // FIX: -48 is a bandaid fix for the output
}

void VectorFloat::ReadFromKeyboard()
{

	cout << "Mata in tecken.." << endl;

	char c;
	
#if 0

	while ((c = _getch()) != 'q')
	{
		for (int i = 0; i < this->vptr->size(); i++)
		{
			cout << c << " ";
			Set(c, i);
		}
	}

#endif // 0

	while(true)
	{
		for (int i = 0; i < this->vptr->size(); i++)
		{
			c = _getch();
			cout << c << " ";
			Set(c, i);

		} break;
	}
}

void VectorFloat::Print()
{
	cout << "\nLista: ";
	cout << "[";
	for (int i = 0; i < this->vptr->size(); i++)
	{
		cout << this->vptr->at(i) << ", ";
	}
	cout << "\b\b]\n\n";
}





