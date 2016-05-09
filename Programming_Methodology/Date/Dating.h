#pragma once
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

#include "PersonList.h"
#include "CoupleList.h"
#include "Person.h"

class Dating
{
	CoupleList couples;
	PersonList females, males;

public:
	Dating()
	{
		ReadFromFile(); //Reads in persons from file to lists
	}

	void matchCouples()
	{
		auto maleindex = 0;

		while (availablePersons())
		{
			auto bestmatch = 0;
			for (auto i = 0; i < males.max_size(); i++)
			{
				auto commonmatch = 0;
				for (auto j = 0; j < females.front().GetInterests().max_size(); j++)
				{
					for (auto l = 0; l < males[i].GetInterests().max_size(); l++)
					{
						if (females.front().GetInterests()[j] == males[i].GetInterests()[l])
						{
							commonmatch++;
						}
					}
				}
				if (commonmatch >= bestmatch)
				{
					bestmatch = commonmatch;
					maleindex = i;
				}
			}

			Couple c(females.front(), males[maleindex]);
			females.pop_front();
			males.pop(maleindex);
			couples.Add(c);
		}
		//couples.sort();

		couples.Display();
	}

	bool availablePersons() const
	{
		return males.max_size() > 0 && females.max_size() > 0;
	}

	void ReadFromFile()
	{
		std::string str, person, strRow;
		std::ifstream fin;

		fin.open("Dejtlist.txt");

		if (!fin.good())
		{
			std::cout << "Could not open file" << std::endl;
			return;
		}

		males.clear();
		females.clear();

		while (getline(fin, strRow))
		{
			std::istringstream iss(strRow);
			getline(iss, person, '=');

			if (person.compare("Person") == 0)
			{
				Person p;
				iss >> p;
				if (p.GetGender() == "Male")
				{
					males.push_front(p);
				}
				else if (p.GetGender() == "Female")
				{
					females.push_front(p);
				}
			}
		}

		fin.close();
	}

#pragma region Display-functions
	void DisplayAllLists() const
	{
		females.Display();
		males.Display();
	}

	void DisplayFemales() const
	{
		females.Display();
	}

	void DisplayMales() const
	{
		males.Display();
	}
#pragma endregion
};

/*
Programmet ska sedan fråga efter antalet gemensamma intressen(till exempel 4), och
för varje flicka i flicklistan försöka hitta en pojke i pojklistan med minst detta antal lika
intressen.

Om en sådan lämplig partner hittas, ska paret stoppas in i en parlista, som ska
vara sorterad efter flicknamn.Flickan ska då också tas bort från flicklistan, och pojken
från pojklistan.
*/

