#pragma once

#if 0
#include <iostream>
#include <range/v3/all.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

inline auto dates_in_year(int year)
{
	return view::iota(date{year, greg::Jan, 1},
	                  date{year, greg::Jan, 1});
}

inline void run_dates_in_year()
{
	auto year = dates_in_year(2015);
// Group into months
	auto months = year | view::group_by([](date a, date b)
		{
			return a.month() == b.month();
		});

// Print the first day of each month
	RANGES_FOR(auto month, months)
	{
		std::cout << front(month) << '\n';
	}
}

#endif

