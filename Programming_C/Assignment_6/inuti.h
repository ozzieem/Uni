#include <stdlib.h>
#include <stdio.h>

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
