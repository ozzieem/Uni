#pragma once
#include "Byr�kraten.h"


void Byr�kraten::random_word()
{
	for (int i = 0; i < int(this->words.size()); i++)
	{
		for (int j = 0; j < 1; j++)
		{
			int rand_word = rand() % this->words[i].size();
			this->new_sentence.push_back(this->words[i][rand_word]);
		}
	}
}

void Byr�kraten::print_sentence()
{	
	cout << endl;

	for (int i = 0; i < int(this->new_sentence.size()); i++)
		cout << this->new_sentence[i] << " ";

	cout << "\b.\n"; //Backspace and dot
}

//Constructor
Byr�kraten::Byr�kraten(vector<vector<string>> vec)
{
	srand(unsigned int(time(NULL)));
	this->words = vec;
}

//Constructor
Byr�kraten::Byr�kraten()
{
	srand(unsigned int(time(NULL)));
	this->words =
	{
		{ "N�r det g�ller", "Betr�ffande", "Mot bakgrund av",
		"I termer av", "Parallellt med", "R�rande" },

		{ "konstruktiv", "konsekvent", "objektiv",
		"seri�s", "konventionell", "dynamisk" },

		{ "information", "rationalisering", "effekt",
		"samordning","�kning", "kravanalys" },

		{ "generaliseras", "verifieras", "utvecklas",
		"f�rordras", "modifieras", "realiseras" },

		{ "principiella", "reella", "fundamentala",
		"latenta", "godtyckliga", "informella", "partiella" },

		{ "rutiner", "strukturer", "tendenser", "hypoteser",
		"ideologier", "konklusioner", "restriktioner" },

		{ "i samband med", "med h�nsyn till", "inom ramen f�r",
		"med avseende p�", "i vad avser", "i fr�ga om" },

		{ "administrationen", "n�ringslivet", "myndigheten",
		"personalen", "intressenterna", "utbudet", "utfallet" }
	};
}

//DEBUG
void Byr�kraten::test_print()
{
	for (unsigned int i = 0; i < this->words.size(); i++) //Unsigned int
	{
		for (int j = 0; j < int(this->words[i].size()); j++) //Eller int()?
			cout << this->words[i][j] << endl;
	}
	
	int size_of_vec = this->words.size();
	cout << "Vector size: " << size_of_vec;
}


