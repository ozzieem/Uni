#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "Console.h"
#include <fstream>

namespace MemorySpace
{

	class Player
	{
	public:
		Player() {}
	};


	class Card
	{
	private:
		string back;
		string front;

	public:

		Card() {}

		void setFront(string str)
		{
			this->front= str;
		}

		void setBack(string value)
		{
			this->back= value;
		}

		string getFront()
		{
			return this->front;
		}

		string getBack()
		{
			return this->back;
		}

	};


	class Memory
	{
	private:
		int nPlayers = 1;
		int nCards = 16; //Must be a n^2 value
		int MatrixSide = int(sqrt(nCards));

		vector<Player> PlayerVector =
			vector<Player>(nPlayers, Player());

		vector<vector<Card>> CardMatrix = 
			vector<vector<Card>>(MatrixSide, 
				vector<Card>(MatrixSide, Card()));

		struct Position
		{
			int x1;
			int y1;
			int x2;
			int y2;
		} fPos, rVal;


	public:
		Memory();

		void CreateCards();
		void GenMemCards();
		void PrintCards();
		void CardFlip(int row, int col);
		void CardNav();
		void CheckCards();
	};


	class HighScoreData
	{

	private:

		vector<Player> players;
		int points;

	public:

		Player getPlayer(int p)
		{
			return this->players[p];
		}

		int getPoints()
		{
			return points;
		}

		void setPoints(int _points)
		{
			this->points = _points;
		}
		
		void addPoints(int _points)
		{
			this->points += _points;
		}

		void subPoints(int _points)	//Allow negative points?
		{
			if (points > 0)
			{
				this->points -= _points;
			}
			else
			{
				this->points = 0;
			}
		}

	};

	class HighScore
	{
	private:
		vector<HighScore> vHighScore;

	public:

		void readFile()
		{

		}

		void writeFile()
		{
			ofstream myfile;
			myfile.open("test.txt");
			myfile << "Test writing to file";
			myfile.close();
		}
	};


}
