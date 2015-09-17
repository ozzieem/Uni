#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Player;
class Card;

namespace MemorySpace
{
	class Memory
	{
	private:
		int nPlayers = 1; //p
		int nCards = 16;	//c
		int MatrixSide = int(sqrt(nCards));

		vector<Player> PlayerVector = 
			vector<Player>(nPlayers, Player()); //pv

		vector<vector<Card>> CardMatrix = 
			vector<vector<Card>>(MatrixSide, 
				vector<Card>(MatrixSide, Card()));	//cvv

	public:
		Memory();

		void CreateCards();
	};


	class Player
	{
	public:
		Player() {}
	};


	class Card
	{
	private:
		string value;

	public:
		Card() {}

		void SetValue(string value)
		{
			this->value = value;
		}

		string GetValue()
		{
			return this->value;
		}
	};
}
