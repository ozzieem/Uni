#pragma once

#include <vector>
#include "Multimedia.h"

class MultimediaRegister
{
private:
	vector<Multimedia> objs;

public:
	void addToFile();
	void removeFromFile();
	void searchFile();

};


