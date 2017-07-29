#pragma once

#include <iostream>
using namespace std;

#include <windows.h>

namespace Course
{
	
	/// <summary>
	/// Simplified interface to some console window functions.
	/// </summary>
	class Console
	{
	public:

		/// <summary>
		/// Sets the cursor position to column x and row y.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		static void gotoxy(int x, int y)
		{
			COORD coordScreen;
			HANDLE hGlobStdOut;

			hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			coordScreen.X=x;
			coordScreen.Y=y;
			SetConsoleCursorPosition(hGlobStdOut, coordScreen);
		}

		/// <summary>
		/// Clears the screen and sets the cursor position to [x,y]=[0,0]
		/// </summary>
		static void clrscr(void)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			DWORD chWritten;
			HANDLE hGlobStdOut;
			COORD coordScreen;

			hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hGlobStdOut, &csbi);
			coordScreen.X=0;
			coordScreen.Y=0;
			FillConsoleOutputCharacter(hGlobStdOut, ' ',csbi.dwSize.Y*csbi.dwSize.X, coordScreen, &chWritten); 
			SetConsoleCursorPosition(hGlobStdOut, coordScreen);
		}

		/// <summary>
		/// Returns the actual x-value of the cursor position.
		/// </summary>
		/// <returns></returns>
		static int wherex(void)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			HANDLE hGlobStdOut;

			hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hGlobStdOut, &csbi);
			return csbi.dwCursorPosition.X;
		}

		/// <summary>
		/// Returns the actual y-value of the cursor position.
		/// </summary>
		/// <returns></returns>
		static int wherey(void)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			HANDLE hGlobStdOut; 

			hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hGlobStdOut, &csbi);
			return csbi.dwCursorPosition.Y;
		}

		/// <summary>
		///  Sätter cursor på om on = 1 och av om on = 0 */
		///  Cursorns  storlek mellan blockcursor om size = 100 och radcursor om size = 1 
		/// </summary>
		/// <param name="on">The on .</param>
		/// <param name="size">The size.</param>
		static void setcursor(int on, int size)
		{
			CONSOLE_CURSOR_INFO ccurinfo;
			HANDLE hGlobStdOut; 

			hGlobStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			ccurinfo.bVisible = on;
			ccurinfo.dwSize = size;
			SetConsoleCursorInfo(hGlobStdOut, &ccurinfo);
		}

		/// <summary>
		/// Sets the title on the window.
		/// </summary>
		/// <param name="str">The STR.</param>
		static void set_console_title(string str)
		{
			TCHAR s[255];
			for (unsigned int i = 0; i < str.length(); i++)
			{
				s[i]=str[i];
				s[i+1]=NULL;
			}

			SetConsoleTitle(s);
		}

		/// <summary>
		/// Sets the sixe of the window in pixels.
		/// </summary>
		/// <param name="w">The w.</param>
		/// <param name="h">The h.</param>
		static void set_console_window_size(int w, int h)
		{
			HWND console = GetConsoleWindow();
			RECT r;
			GetWindowRect(console, &r);

			MoveWindow(console, r.left, r.top, w, h, TRUE);
		}

		
		/// <summary>
		/// General function to set the color in text window.
		/// </summary>
		/// <param name="foregroundRed">The foreground red.</param>
		/// <param name="foregroundGreen">The foreground green.</param>
		/// <param name="foregroundBlue">The foreground blue.</param>
		/// <param name="foregroundIntensity">The foreground intensity.</param>
		/// <param name="backgroundRed">The background red.</param>
		/// <param name="backgroundGreen">The background green.</param>
		/// <param name="backgroundBlue">The background blue.</param>
		/// <param name="backgroundIntensity">The background intensity.</param>
		static void set_color(boolean foregroundRed, 
			boolean foregroundGreen, 
			boolean foregroundBlue,
			boolean foregroundIntensity,
			boolean backgroundRed, 
			boolean backgroundGreen, 
			boolean backgroundBlue,
			boolean backgroundIntensity
			)
		{
			WORD c = 0;
			c = c + ((foregroundRed       ? 1 : 0)<<2);
			c = c + ((foregroundGreen     ? 1 : 0)<<1);
			c = c + ((foregroundBlue      ? 1 : 0)<<0);
			c = c + ((foregroundIntensity ? 1 : 0)<<3);
			c = c + ((backgroundRed       ? 1 : 0)<<6);
			c = c + ((backgroundGreen     ? 1 : 0)<<5);
			c = c + ((backgroundBlue      ? 1 : 0)<<4);
			c = c + ((backgroundIntensity ? 1 : 0)<<7);


			HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
			HANDLE hstdout= GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hstdout, c);
		}

		/// <summary>
		/// Set the foreground color to red.
		/// </summary>
		static void set_foreground_red()
		{
			set_color(true,false,false,true,false,false,false,false);
		}

		/// <summary>
		/// Set the foreground color to green.
		/// </summary>
		static void set_foreground_green()
		{
			set_color(false,true,false,true,false,false,false,false);
		}

		/// <summary>
		/// Set the foreground color to blue.
		/// </summary>
		static void set_foreground_blue()
		{
			set_color(false,false,true,true,false,false,false,false);
		}
	};
}

