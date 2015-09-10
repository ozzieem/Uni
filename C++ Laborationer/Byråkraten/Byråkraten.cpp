#pragma once
#include "Byråkraten.h"


void Byråkraten::random_word()
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

void Byråkraten::print_sentence()
{	
	cout << endl;

	for (int i = 0; i < int(this->new_sentence.size()); i++)
		cout << this->new_sentence[i] << " ";

	cout << "\b.\n"; //Backspace and dot
}

//Constructor
Byråkraten::Byråkraten(vector<vector<string>> vec)
{
	srand(unsigned int(time(NULL)));
	this->words = vec;
}

//Constructor
Byråkraten::Byråkraten()
{
	srand(unsigned int(time(NULL)));
	this->words =
	{
		{ "När det gäller", "Beträffande", "Mot bakgrund av",
		"I termer av", "Parallellt med", "Rörande" },

		{ "konstruktiv", "konsekvent", "objektiv",
		"seriös", "konventionell", "dynamisk" },

		{ "information", "rationalisering", "effekt",
		"samordning","ökning", "kravanalys" },

		{ "generaliseras", "verifieras", "utvecklas",
		"förordras", "modifieras", "realiseras" },

		{ "principiella", "reella", "fundamentala",
		"latenta", "godtyckliga", "informella", "partiella" },

		{ "rutiner", "strukturer", "tendenser", "hypoteser",
		"ideologier", "konklusioner", "restriktioner" },

		{ "i samband med", "med hänsyn till", "inom ramen för",
		"med avseende på", "i vad avser", "i fråga om" },

		{ "administrationen", "näringslivet", "myndigheten",
		"personalen", "intressenterna", "utbudet", "utfallet" }
	};
}

//DEBUG
void Byråkraten::test_print()
{
	for (unsigned int i = 0; i < this->words.size(); i++) //Unsigned int
	{
		for (int j = 0; j < int(this->words[i].size()); j++) //Eller int()?
			cout << this->words[i][j] << endl;
	}
	
	int size_of_vec = this->words.size();
	cout << "Vector size: " << size_of_vec;
}


