#include "Log.h"

#include "Time.h"

Log::Log()
{
	Time time;
	this->m_timeStamp = time.getStringCurrentDateTime();
}

void Log::receiveLogData()
{
	std::cout << "Enter your log data (" << this->m_timeStamp << "): \n";
	this->m_text += "--------------" + this->m_timeStamp + "--------------" + "\n";
	std::string inputText;
	while (std::cin.peek() != '\n')
	{
		std::cin >> inputText;
		this->m_text += inputText + " ";
	}
}

std::ostream & operator<<(std::ostream & out, Log & l)
{
	out << l.m_text;
	return out;
}
