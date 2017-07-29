#include "Time.h"

Time::Time()
{
	time_t now = time(0);
	localtime_s(&this->m_currentTime, &now);

	this->m_year = this->getCurrentYear();
	this->m_month = this->getCurrentMonth();
	this->m_day = this->getCurrentDay();

	this->m_hour = this->getCurrentHour();
	this->m_minute = this->getCurrentMinute();
	this->m_second = this->getCurrentSecond();
}

std::int16_t Time::getCurrentYear()
{
	return this->m_currentTime.tm_year + 1900;
}

std::int16_t Time::getCurrentMonth()
{
	return this->m_currentTime.tm_mon;
}

std::int16_t Time::getCurrentDay()
{
	return this->m_currentTime.tm_mday;
}

std::int16_t Time::getCurrentHour()
{
	return this->m_currentTime.tm_hour;
}

std::int16_t Time::getCurrentMinute()
{
	return this->m_currentTime.tm_min;
}

std::int16_t Time::getCurrentSecond()
{
	return this->m_currentTime.tm_sec;
}

std::ostream & operator<<(std::ostream & out, Time t)
{
	out << t.m_year << "-";
	if (t.m_month < 10) out << "0";
	out << t.m_month << "-";
	if (t.m_day < 10) out << "0";
	out << t.m_day << " ";
	out << t.m_hour << ":" << t.m_minute << ":" << t.m_second << "\n";
	return out;
}

std::string Time::getStringCurrentDay() 
{
	std::string s = std::to_string(this->m_year) + "-";
	if (this->m_month < 10) s += "0";
	s += std::to_string(this->m_month) + "-";
	if (this->m_day < 10) s += "0";
	s += std::to_string(this->m_day) + " ";
	return s;
}

std::string Time::getStringCurrentTime()
{
	std::string s;
	if (this->m_hour < 10) s += "0";
	s += std::to_string(this->m_hour) + ":";
	if (this->m_minute < 10) s += "0";
	s += std::to_string(this->m_minute) + ":";
	if (this->m_second < 10) s += "0";
	s += std::to_string(this->m_second);
	return s;
}

std::string Time::getStringCurrentDateTime() 
{
	std::string s = std::to_string(this->m_year) + "-";
	if (this->m_month < 10) s += "0";
	s += std::to_string(this->m_month) + "-";
	if (this->m_day < 10) s += "0";
	s += std::to_string(this->m_day) + " ";
	if (this->m_hour < 10) s += "0";
	s += std::to_string(this->m_hour) + ":";
	if (this->m_minute < 10) s += "0";
	s += std::to_string(this->m_minute) + ":";
	if (this->m_second < 10) s += "0";
	s += std::to_string(this->m_second);
	return s;
}