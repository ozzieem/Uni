#include "Libs.h"

// Swap int values by value, reference and pointer

static void swap1(int a, int b) {
	int tmp = a;
	a = b;
	b = tmp;
}


static void swap2(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}


static void swap3(int* a, int* b) {
	int* tmp = a;
	a = b;
	b = tmp;
}

static void RunSwap() {

	int a = 10;
	int b = 20;
	swap1(a, b);
	printf("a=%i, b=%i\n", a, b);

	int c = 10;
	int d = 20;
	swap2(c, d);
	printf("c=%i, d=%i\n", c, d);

	int e = 10;
	int f = 20;
	swap3(&e, &f);
	printf("e=%i, f=%i\n", e, f);
}