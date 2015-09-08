#include <iostream>


int main(int argc, char *argv[])
{
	std::cout << "Value of argc: " << argc << std::endl;

	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;

	std::cin.get();
}