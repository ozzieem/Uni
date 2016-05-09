#pragma once
#include "Person.h"

using std::cout;
using std::endl;

class PersonList : public forwardList<Person>
{
public:
	PersonList()
	{
	}

	void Display() const
	{
		cout << "Total entities: " << max_size() << endl;
		for (auto& it : *this)
		{
			cout << "Name: " << it.data.GetName() << " (" << it.data.GetGender() << ")" << endl;
			cout << "Interests: ";

			for (auto& interest : it.data.GetInterests())
			{
				cout << interest.data << " ";
			}

			cout << endl << endl;
		}
	}
};

