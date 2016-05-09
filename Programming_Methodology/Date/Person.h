#pragma once
#include <string>

#include "InterestTable.h"

class Person
{
	friend std::istream& operator>>(std::istream& in, Person& person)
	{
		std::string s, tempInterest;

		getline(in, person.name, '-');
		getline(in, person.gender, ':');
		while (!in.eof())
		{
			getline(in, tempInterest, ',');
			person.interests.Add(tempInterest);
		}

		return in;
	}

	std::string name;
	std::string gender;
	InterestTable interests;

public:

	Person()
	{
		name = "";
		gender = "";
	}

	Person(std::string _name, std::string _gender, InterestTable interest) :
		name(_name), gender(_gender), interests(interest)
	{
	}

	std::string GetName() const
	{
		return name;
	}

	std::string GetGender() const
	{
		return gender;
	}

	InterestTable GetInterests() const
	{
		return interests;
	}
};

