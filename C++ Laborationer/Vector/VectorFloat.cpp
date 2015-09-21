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
	this->vptr = new float[s];
	this->size = s;
}	

void VectorFloat::DeleteVector()
{
	delete this->vptr;
	this->size = 0;
}

void VectorFloat::Set(float value, int index)
{
#if 0
	try
	{
		if (index < 0 || index > this->size)
		{
			throw "index is less than 0 or out of bound";
		}
	}
	catch (bad_typeid)
	{
		cerr << "Not correct type";
	}
#endif	

	(*this).vptr[index] = value;
}

void VectorFloat::ReadFromKeyboard()
{

	cout << "Enter " << this->size << " digits... (separate with space)" << endl;

	float c;
	
	while(true)
	{
		for (int i = 0; i < this->size; i++)
		{
			cin >> c;
			Set(c, i);

		} break;
	}
}

void VectorFloat::Print()
{
	cout << "\nList: ";
	cout << "[";
	for (int i = 0; i < this->size; i++)
	{
		cout << (*this).vptr[i]<< ", ";
	}
	cout << "\b\b]\n\n";
}





