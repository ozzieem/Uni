#pragma once
#include <iostream>
#include "Console.h"
#include <cstdlib>
#include <conio.h>

using namespace std;
using namespace Course;

class TicTacToe
{

public:

	char board[3][3];
	int xcursor, ycursor;

	TicTacToe()
	{
		this->xcursor = 32;
		this->ycursor = 11;
	}

	void setup_board(char p[3][3]);
	int check_winner(char p[3][3]);
	void input_checker(char c);
	void update_cursor_position();
	void announce_winner(int n);

};