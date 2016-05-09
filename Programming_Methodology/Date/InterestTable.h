#pragma once
#include "../ForwardList/FList.h"

class InterestTable : public forwardList<std::string>
{
public:

	InterestTable()
	{
	}

	void Add(std::string _interest)
	{
		push_front(_interest);
	}
};

