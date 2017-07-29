#pragma once
#include <vector>
#include <list>
#include <algorithm>


#if 0
//--- Initialization ---//

	int x1; // Unknown
	int x2; // (At global scope) 0
	static int x3; // 0
	int* px = new int; // Unknown - Runtime cost
	{
		int x4; // Unknown - Incurs a runtime cost to give it a value
	}
	int a1[100]; // Unknown
	int a2[100]; // (At global scope) 0 - Can be conceptualized before runtime, no cost 
	static int a3[100]; // 0
	std::vector<int> v(100); // 0 - Allocated on heap, incurs a runtime cost
#endif

#if 0
//--- Type Deducation ---//
	
	const int cx = 0;

	auto my_cx1 = cx; // int

	decltype(cx) my_cx2 = cx; // const int

	template <typename T>
	void f1(T param);
	f1(cx); // int

	template <typename T>
	void f2(T& param);
	f2(cx); // const int

	template <typename T>
	void f3(T&& param);
	f3(cx); // const int& - Behaves this way to allow argument forwarding

	auto lam = [cx] { cx = 10; };	// error!
	auto lam1 = [cx = cx] mutable { cx = 10; };	// error!
	auto lam2 = [cx = cx]() mutable { cx = 10; };	// allowed

#endif

#if 0
//--- Computational Complexity ---//

	std::vector<int> v;

	std::sort(v.begin(), v.end());	
// Compiles, sort requires random access iterators. 
// Vector offers those iterators. Complexity: O(n lg n)

	std::list<int> li;

	std::sort(li.begin(), li.end());
// Does NOT compile. List does not have random access iterator.
	
	auto it1 =
		std::binary_search(v.begin(), v.end(), 10);
// Compiles. Binary search - Complexity O(lg n)

	auto it2 = 
		std::binary_search(li.begin(), li.end(), 10);
// Compiles. Complexity O(n). Linear. 
#endif

#if 0
//--- Essential Complexity ---//

struct Point
{
	int x, y;
};

// Type of Point::x? - int

Point p;
const Point& cp = p;
// Type of cp.x? - int but is const int too:
// C++ solution:
// decltype(cp.x) = int
// decltype((cp.x)) = const int&
#endif

