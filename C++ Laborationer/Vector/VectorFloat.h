#pragma once

#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;

class VectorFloat
{
private:

	vector<float> *vptr;
	int size;
	
	void CreateVector(int);
	void DeleteVector();

public:

	VectorFloat();
	VectorFloat(int);
	~VectorFloat();

	void Set(float, int);
	void ReadFromKeyboard();
	void Print();

};
