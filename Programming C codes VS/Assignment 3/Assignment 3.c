#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int inuti(double x, double y, double x1, double y1, double x2, double y2) {
	int x_inuti;
	int y_inuti;

	if (x1 < x2)
		x_inuti = x > x1 && x < x2;
	else
		x_inuti = x > x2 && x < x1;
	if (y1 < y2)
		y_inuti = y > y1 && y < y2;
	else
		y_inuti = y > y2 && y < y1;
	return x_inuti && y_inuti;
}

int main(void) {
	int i;

	double x[] = { -1.49999999999888,	5.09999999,		8999999999999999999.0,		11,		13.3,	0.21,	0.99 };
	double y[] = { 3,					3.499999999,	8999999999999999999.0,		2.4,	9,		3.8,	0.99 };

	double x1[] = { -1.5,				5.1,			-900000000000000000.0,		1.2,	4,		-5,		-1 };
	double y1[] = { 2,					3.5,			-900000000000000000.0,		-2,		15,		-0.22,	-1 };

	double x2[] = { 5,					3.5,			9000000000000000000.0,		-2,		23,		0.22,	1 };
	double y2[] = { 4.9,				6.3,			9000000000000000000.0,		6,		28,		8,		1 };


	int result[] = { 1, 1, 1, 0, 1, 1, 1 };


	for (i = 0; i < (sizeof(result) / sizeof(int)); i++){ /* sizeof - length of array*/
		int result;

		result = inuti(x[i], y[i], x1[i], y1[i], x2[i], y2[i]);

		if (result == 0)
			printf("Error. Dot (%f, %f) is not in the expected position.\n", x[i], y[i]);

		printf("\n");
	}

	_getch();
	return 0;
}