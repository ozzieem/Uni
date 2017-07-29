#pragma once

#include <fstream>

template<typename T>
class FileHandler
{
public:
	std::string m_fileName;
	FileHandler(std::string fileName) : m_fileName(fileName) {};

	void writeToFile(T content) 
	{
		try
		{
			std::fstream fs;
			fs.open(this->m_fileName, std::fstream::app);

			fs.seekp(0, std::ios::end);
			fs << "\n" << content << "\n";

			fs.close();
		}
		catch (std::exception e)
		{
		}
	}
};

