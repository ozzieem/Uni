#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "Console.h"

using namespace std;
using namespace Course;

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
		string value;
		string memVal;

	public:

		Card() {}

		void SetmemVal(string str)
		{
			this->memVal = str;
		}

		void SetValue(string value)
		{
			this->value = value;
		}

		string GetmemVal()
		{
			return this->memVal;
		}

		string GetValue()
		{
			return this->value;
		}

	};


	class Memory
	{
	private:
		int nPlayers = 1;	//p
		int nCards = 16;	//c
		int MatrixSide = sqrt(nCards);

		vector<Player> PlayerVector =
			vector<Player>(nPlayers, Player());	//pv

		vector<vector<Card>> CardMatrix = 
			vector<vector<Card>>(MatrixSide, 
				vector<Card>(MatrixSide, Card()));	//cvv

	public:
		Memory();

		void CreateCards();
		void GenMemCards();
		void PrintCards();
		void cardFlip();
	};

}
