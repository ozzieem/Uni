#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include "Console.h"

using namespace std;
using namespace Course;

class Byr�kraten
{
private:
	vector<vector<string>> words;
	vector<string> new_sentence;

public:
	Byr�kraten(vector<vector<string>>);
	Byr�kraten();

	void random_word();
	void print_sentence();
	void test_print(); //DEBUG
};

