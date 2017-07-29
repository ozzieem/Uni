#include <conio.h>
#include <iostream>
#include <sstream>
#include <locale>

#include "Time.h"
#include "Log.h"
#include "FileHandler.h"


int main() {

	std::locale swedish("swedish");
	std::locale::global(swedish);

	Log log;
	log.receiveLogData();

	FileHandler<std::string> fh("AtlasCopcoLog.txt");
	fh.writeToFile(log.m_text);

	std::cout << 
		"\n================== Generated Log =========================\n" << 
		log <<
		"\n==========================================================\n" << 
		"Written to file " << fh.m_fileName;

	_getch();
}