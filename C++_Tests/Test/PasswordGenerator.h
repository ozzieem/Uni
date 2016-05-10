#pragma once
#include<iostream>
#include<string>
#include <time.h>

const std::string alphanum =
"0123456789abcdefghijklmnopqrstuvwxyz!@#$%^&*_+ABCDEFGHIJKLMNOPQRSTUVWXYZ";

inline void GeneratePassword()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::cout << "Enter password length:";
	int pw_len;
	std::cin >> pw_len;

	std::string password;

	for (auto i = 0; i < pw_len; i++)
	{
		int random_letter = rand() % alphanum.length();
		password += alphanum[random_letter];
	}

	std::cout << password << std::endl;
}

