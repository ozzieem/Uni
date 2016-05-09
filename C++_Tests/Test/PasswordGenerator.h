#pragma once
#include<iostream>
#include<string>
#include <time.h>

const std::string alphanum =
"0123456789abcdefghijklmnopqrstuvwxyz!@#$%^&*_+ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void GeneratePassword()
{
	srand(time(nullptr));
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
