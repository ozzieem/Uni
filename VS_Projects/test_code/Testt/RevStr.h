#include "Libs.h"
#if 0
static void ReverseWithPointer(char* str)
{

	std::cout << str << " -> ";

	char* start = str;
	char* end = str;

	if (strlen(str) % 2)
		end = str + sizeof(str);
	else
		end = str + sizeof(str) + 1;
	
	while (end > start)
	{
		char tmp = *start;
		*start++ = *end;
		*end-- = tmp;
	}

	printf("%s\n", str);
}
#endif

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
	//ReverseWithPointer(buffer);
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
