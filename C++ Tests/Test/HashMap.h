#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

void HashMap()
{
	std::unordered_map<std::string, std::string> u = {
		{ "RED","#FF0000" }, { "GREEN","#00FF00" }, { "BLUE","#0000FF" }
	};

	for (const auto& n : u) {
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
	}

	u["BLACK"] = "#000000";
	u["WHITE"] = "#FFFFFF";

	for (auto& n : u)
	{
		std::cout << "The HEX of color " << n.first << " is:[" << n.second << "]\n";
	}
}
