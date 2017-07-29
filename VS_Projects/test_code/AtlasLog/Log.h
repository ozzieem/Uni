#pragma once

#include <stdlib.h>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>

class Log
{
public:
	std::string m_text;
	std::string m_timeStamp;

	friend std::ostream &operator<<(std::ostream &out, Log &l);

	Log();

	void receiveLogData();
};

