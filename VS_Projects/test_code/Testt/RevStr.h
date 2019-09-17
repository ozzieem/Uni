#include "Libs.h"

static int GetStringLength(char* s) {
	int len = 0;
	while (*s++ != '\0') len++;
	return len;
}

static void SwapChar(char &s1, char &s2) {
	char tmp = s1;
	s1 = s2;
	s2 = tmp;
}

static void SwapCharWithPointers(char* ch1_ptr, char* ch2_ptr)
{
	char swap_ptr = *ch1_ptr;
	*ch1_ptr = *ch2_ptr;
	*ch2_ptr = swap_ptr;
}

static void ReverseWithPointer(char* str)
{
	std::cout << str << " -> ";

	const short length = GetStringLength(str);

	// Set pointers to beginning of string
	char* begin_ptr = str;
	char* end_ptr = str;

	// Move the end_ptr to the last character 
	for (unsigned int i = 0; i < length - 1; i++)
	{
		end_ptr++;
	}

	char swap_ptr;

	for (unsigned int i = 0; i < length / 2; i++) {

		// Swap the pointers with eachother, thus swapping the character they point to
		SwapCharWithPointers(end_ptr, begin_ptr);

		// and move pointers to the new characther
		begin_ptr++;
		end_ptr--;
	}

	printf("%s\n", str);
}

static void ReverseWithArray(char* s) {
	std::cout << s << " -> ";

	int length = GetStringLength(s);
	int last = length - 1;
	for (int i = 0; i < length / 2; ++i)
	{
		SwapChar(s[i], s[last - i]);
	}

	printf("%s\n", s);
}

static void RunReverseWithPointer(char s[]) {
	char buffer[16];
	strcpy_s(buffer, s);
	ReverseWithPointer(buffer);
}

static void RunReverseWithArray(char s[]) {
	char buffer[16];
	strcpy_s(buffer, s);
	ReverseWithArray(buffer);
}

static void RunReverseString() {

	std::cout << "ReverseWithPointer:\n";
	RunReverseWithPointer("hello");
	RunReverseWithPointer("backward");
	RunReverseWithPointer("he");
	RunReverseWithPointer("h");


	std::cout << "ReverseWithArray:\n";
	RunReverseWithArray("hello");
	RunReverseWithArray("backward");
	RunReverseWithArray("he");
	RunReverseWithArray("h");
}
