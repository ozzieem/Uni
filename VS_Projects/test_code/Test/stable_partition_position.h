#pragma once
#include <algorithm>

template <typename I, typename P>
auto stable_partition_position(I f, I l, P p) -> I
{
	auto n = l - f;
	if (n == 0) return f;
	if (n == 1) return f + p(f);

	auto m = f + (n / 2);

	return std::rotate(stable_partition_position(f, m, p),
	                   m,
	                   stable_partition_position(m, l, p));
}

inline void stable_partition_test()
{
	int a[] = {1,2,3,4,5,5,4,3,2,1};
	bool b[] = {0,1,0,1,0,0,1,0,1,0};

	auto p = stable_partition_position(
		std::begin(a), std::end(a), [&](auto i)
		{
			return *(std::begin(b) + (i - std::begin(a)));
		});

	for (auto f = std::begin(a), l = p; f != l; ++f) std::cout << *f << " ";
	std::cout << "^ ";
	for (auto f = p, l = std::end(a); f != l; ++f) std::cout << *f << " ";
	std::cout << std::endl;
}

