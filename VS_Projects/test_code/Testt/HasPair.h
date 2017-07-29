#pragma once

#include "Libs.h"

static bool MyHasPairWithSum(const std::vector<int> data, int sum) {
	for (auto val = 0; val < data.size(); val++) {
		for (auto nextVal = val + 1; nextVal < data.size(); nextVal++) {
			if (data[val] + data[nextVal] == sum) {
				return true;
			}
		}
	}
	return false;
}

static bool HasPairWithSum(const std::vector<int> data, int sum) {
	std::unordered_set<int> comp;
	for (auto& value : data) {
		if (comp.find(value) != comp.end()) {
			return true;
		}
		comp.insert(sum - value);
	}
	return false;
}

static bool RunTest(const std::vector<int> data, int sum) {
	auto test1 = MyHasPairWithSum(data, sum);
	//std::cout << "MyHasPairWithSum Returned " << test1 << " with Sum " << sum << '\n';

	auto test2 = HasPairWithSum(data, sum);
	//std::cout << "HasPairWithSum Returned " << test2 << " with Sum " << sum << '\n';

	return test1 == test2;
}

static void RunTestAll(const std::vector<int> data, int maxVal) {
	for (auto val = 0; val < maxVal; ++val) {
		auto testStatus = RunTest(data, val);
		if (!testStatus) {
			std::cout << "Test failed at iteration " << val << '\n';
			return;
		}
	}
	std::cout << "All tests passed\n";
}

static void RunHasPair() {
	std::vector<int> v1 = { 1, 2, 3, 9 };
	std::vector<int> v2 = { 1, 3, 4, 4 };

	auto sumTest = 7;

	RunTestAll(v1, 100);
}
