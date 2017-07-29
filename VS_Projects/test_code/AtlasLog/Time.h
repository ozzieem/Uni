#pragma once

#include <stdlib.h>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>

class Time 
{
private:
	std::int16_t m_year;
	std::int16_t m_month;
	std::int16_t m_day;
	std::int16_t m_hour;
	std::int16_t m_minute;
	std::int16_t m_second;

	friend std::ostream &operator<<(std::ostream &out, Time t);

	struct tm m_currentTime;

public:
	Time();

	std::int16_t getCurrentYear();
	std::int16_t getCurrentMonth();
	std::int16_t getCurrentDay();
	std::int16_t getCurrentHour();
	std::int16_t getCurrentMinute();
	std::int16_t getCurrentSecond();
	std::string getStringCurrentDay();
	std::string getStringCurrentTime();
	std::string getStringCurrentDateTime();
};

