/* MSViscon.h -- 041012 */
/* Funktioner för hantering av Console-fönstret */

#include <windows.h>	

void gotoxy(int x, int y)
{
	COORD coordScreen;
	HANDLE hGlobStdOut;

	hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	coordScreen.X = x;
	coordScreen.Y = y;
	SetConsoleCursorPosition(hGlobStdOut, coordScreen);
}

void clrscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD chWritten;
	HANDLE hGlobStdOut;
	COORD coordScreen;

	hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hGlobStdOut, &csbi);
	coordScreen.X = 0;
	coordScreen.Y = 0;
	FillConsoleOutputCharacter(hGlobStdOut, ' ', csbi.dwSize.Y*csbi.dwSize.X, coordScreen, &chWritten);
	SetConsoleCursorPosition(hGlobStdOut, coordScreen);
}

int wherex(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hGlobStdOut;

	hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hGlobStdOut, &csbi);
	return csbi.dwCursorPosition.X;
}

int wherey(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hGlobStdOut;

	hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hGlobStdOut, &csbi);
	return csbi.dwCursorPosition.Y;
}

void setcursor(int on, int size)
{
	CONSOLE_CURSOR_INFO ccurinfo;
	HANDLE hGlobStdOut;

	hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ccurinfo.bVisible = on;
	ccurinfo.dwSize = size;
	SetConsoleCursorInfo(hGlobStdOut, &ccurinfo);
}
