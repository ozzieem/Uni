#pragma once
#include "Person.h"

class Couple
{
	Person female, male;

public:
	Couple()
	{
		female = Person();
		male = Person();
	}

	Couple(Person _female, Person _male) :
		female(_female), male(_male)
	{
	}

	Person GetFemale() const
	{
		return female;
	}

	Person GetMale() const
	{
		return male;
	}
};

