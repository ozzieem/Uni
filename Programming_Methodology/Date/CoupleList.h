#pragma once
#include "Couple.h"

class CoupleList : public forwardList<Couple>
{
public:
	CoupleList()
	{
	}

	void Add(Couple couple)
	{
		if (empty())
		{
			push_front(couple);
		}
		else
		{
			int firstName = front().GetFemale().GetName().at(0);
			int lastName = last().GetFemale().GetName().at(0);
			int femaleName = couple.GetFemale().GetName().at(0);

			if (femaleName > firstName && femaleName < lastName)
			{
				insert_after(0, couple);
			}
			else if (femaleName < firstName)
			{
				push_front(couple);
			}
			else if (femaleName > lastName)
			{
				push_back(couple);
			}
		}
	}

	void Display()
	{
		cout << "MATCHED " << max_size() << " COUPLES:" << endl;
		for (auto& it : *this)
		{
			cout
				<< it.data.GetFemale().GetName()
				<< " matched with "
				<< it.data.GetMale().GetName()
				<< endl;

			cout << endl;
		}
	}
};

