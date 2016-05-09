/* Luffstud.c -- 2014-02-26 */

#include <stdio.h>
#include <conio.h>
#include "MSViscon.h"

#define ESC 27

/* Fyller matrisen med blanktecken, som betyder tomma rutor */
void rensa(char p[3][3]) {
	int rad, kol;

	for (rad = 0; rad < 3; rad++)
		for (kol = 0; kol < 3; kol++)
			p[rad][kol] = ' ';
}

/* Returns 1 if there's a winner, otherwise returns 0 */
int kontrollera(char p[3][3])
{
	int count = 0;
	int row, column;

	// To try and not violate the DRY-rule, I tried to make a function for the repeating code in the for-loops
	// but I couldn't find a way to do it without it ruining the detection of the characters.

	// To separate the x and o count from eachother, x is incrementing and o is decrementing for each detection in a row, column and diagonal.

	// Checking 3 rows:
	for (row = 0; row < 3; ++row)
	{
		count = 0;
		for (column = 0; column < 3; ++column)
		{
			if (p[row][column] == 'x')
				count++;
			else if(p[row][column] == 'o')
				count--;
		}
		if (count == 3 || count == -3)
		{
			return abs(count/count); // Returns 1 
		}
	}

	// Checking 3 columns:
	for (column = 0; column < 3; ++column)
	{
		count = 0;
		for (row = 0; row < 3; ++row)
		{
			if (p[row][column] == 'x')
				count++;
			else if (p[row][column] == 'o')
				count--;
		}
		if (count == 3 || count == -3)
		{
			return abs(count / count); 
		}
	}

	// Checking diagonal downward from left to right:
	count = 0;
	for (column = 0; column < 3; ++column)
	{
		if (p[column][column] == 'x')
			count++;
		else if (p[column][column] == 'o')
			count--;
	}
	if (count == 3 || count == -3)
	{
		return abs(count / count); 
	}

	// Checking diagonal upward from left to right:
	count = 0;
	for (column = 0; column < 3; ++column)
	{
		if (p[column][2-column] == 'x')
			count++;
		else if (p[column][2-column] == 'o')
			count--;
	}
	if (count == 3 || count == -3)
	{
		return abs(count / count); 
	}

	return 0;	// If there's no return 1 from the above loops
}

/* Ritar upp brädet på skärmen */
void visa(char p[3][3]) {
	int rad, kol;
	char ram[7][14] = {
		"\332\304\304\304\302\304\304\304\302\304\304\304\277",
		"\263\040\040\040\263\040\040\040\263\040\040\040\263",
		"\303\304\304\304\305\304\304\304\305\304\304\304\264",
		"\263\040\040\040\263\040\040\040\263\040\040\040\263",
		"\303\304\304\304\305\304\304\304\305\304\304\304\264",
		"\263\040\040\040\263\040\040\040\263\040\040\040\263",
		"\300\304\304\304\301\304\304\304\301\304\304\304\331"
	};

	clrscr();

	/* skriv ledtext */
	gotoxy(10, 5);
	printf("Move with the arrow-keys and check with RETURN!");

	/* rita ram med övre vänstra hörnet på rad 10 kolumn 30 */
	for (rad = 0; rad <= 6; rad++) {
		gotoxy(30, 10 + rad);
		for (kol = 0; kol <= 12; kol++)
			putchar(ram[rad][kol]);
	}

	/* rita markeringarna */
	for (rad = 0; rad < 3; rad++) {
		for (kol = 0; kol < 3; kol++) {
			gotoxy(30 + 4 * kol + 2, 10 + 2 * rad + 1);
			if (p[rad][kol] == 'x')
				printf("%c", 'x');
			else if (p[rad][kol] == 'o')
				printf("%c", 'o');
		}
	}
}

void markera(int d, char p[3][3]) {
	static int rad = 0, kol = 0; /* Behåller värdet mellan anropen */
	char ch;

	/* välj utseende och startposition för markör */
	setcursor(1, 100);
	if (d == 1)
		gotoxy(32 + 4 * 1, 11 + 2 * 1);
	else
		gotoxy(32 + 4 * kol, 11 + 2 * rad);

	/* flytta omkring med piltangenterna */
	while (1) {
		rad = (wherey() - 11) / 2;
		kol = (wherex() - 32) / 4;

		if (_kbhit()) {
			ch = _getch();
			if (ch == 0 || ch == -32) {
				ch = _getch();
				if (ch == 77 && wherex() < 40)
					gotoxy(wherex() + 4, wherey());
				else if (ch == 75 && wherex() > 32)
					gotoxy(wherex() - 4, wherey());
				else if (ch == 80 && wherey() < 15)
					gotoxy(wherex(), wherey() + 2);
				else if (ch == 72 && wherey() > 11)
					gotoxy(wherex(), wherey() - 2);
			}
			/* markera och avbryt om RETURN och ledig plats */
			else if (ch == 13 && p[rad][kol] == ' ') {
				if (d % 2 == 0)
					p[rad][kol] = 'o';
				else
					p[rad][kol] = 'x';
				setcursor(0, 100);
				break;
			}
		}
	}
}

int main() {
	char spelplan[3][3];
	int drag, klart;

	do {
		rensa(spelplan);
		visa(spelplan);

		/* spela en omgång */
		klart = 0;
		for (drag = 1; drag <= 9 && !klart; drag++) {
			markera(drag, spelplan);
			visa(spelplan);

			/* kontrollera vinnare om 5 markeringar eller fler */
			if (drag >= 5)
				klart = kontrollera(spelplan);
		}

		/* skriv omgångens resultat */
		gotoxy(30, 20);
		if (!klart)
			printf("Tie!");
		else if (drag % 2 == 0)
			printf("x wins!");
		else
			printf("o wins!");

		/* ny omgång? */
		gotoxy(5, 23);
		printf("Program is constructed by \224zgun Mirtchev, Duy Dinh and David Sturesson.");
		gotoxy(15, 24);
		printf("Press any key to play again! (ESC to exit)");
	} while (_getch() != ESC);

	return 0;
}
