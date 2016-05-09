#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class HighScore
{

private:

	vector<HighScoreData> hs;

public:

	void ReadToFile();
	void WriteToFile();


};
