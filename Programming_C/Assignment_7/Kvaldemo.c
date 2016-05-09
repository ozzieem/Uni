/* Kvaldemo.c -- 2014-02-26 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include "MSViscon.h"

struct seriepost {
	int totnr;		// Total resistances
	int outnr;		// Total deviation over/under 5%
	float medel;	// Total average
};

/*//Provade denna gotoxy function istället för MSViscon funktionen men fungerade inte bra
void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}*/



FILE *oppna_strom(void) {
	FILE *tsin;
	char filnamn[30];

	do {
		clrscr();
		gotoxy(10, 10);
		printf("Enter the filename <Press ENTER to read Measure.txt> : ");
		gets(filnamn);
		if (filnamn[0] != '\0')
			tsin = fopen(filnamn, "rt");
		else
			tsin = fopen("Measure.txt", "rt");
		if (tsin == NULL) {
			gotoxy(30, 20);
			printf("This file doesn't exist!\n");
			gotoxy(30, 22);
			printf("Press a key! (ESC to close!)");
			if (_getch() == 27)
				exit(1);
		}
	} while (tsin == NULL);
	return tsin;
}

int las_data(FILE *tsin, struct seriepost serier[])
{

	//Nominalvalue with deviation-values
	const int parValue = 220;	
	double maxValue = parValue * 1.05;
	double minValue = parValue * 0.95; 

	int arrays = 0;
	int numb_qty = 0;
	int arrayNumb = 0;
	int deviations = 0;

	float numb = 0.0;
	float average = 0.0;

	//while fgetc(tsin) != EOF -- Läser första tecknet men kastar bort det, använd fscanf istället såsom nedan.

	while (fscanf(tsin, "%f ", &numb) != EOF)
	{
		if (numb == 0.0)
		{
			average = average / numb_qty;
			serier[arrayNumb].totnr = numb_qty;
			serier[arrayNumb].outnr = deviations;
			serier[arrayNumb].medel = average;
			arrayNumb++;
			arrays++;
			numb_qty = 0;
			deviations = 0;
			average = 0.0;
		}

		else
		{
			numb_qty++;
			average += numb;
			if (numb < minValue || numb > maxValue)
				deviations++;
		} //else
	} //while

	return arrayNumb; //Return total number of arrays

} //main


void visa_stat(struct seriepost serier[], int antal_serier)
{
	const double parValue = 220.0;
	int i, percent_int;
	int tot_qty = 0.0;
	int tot_out = 0.0;

	double p_out = 0.0;
	double percent = 0.0;

	clrscr();

	//gotoxy(3, 0);
	printf("%12s", "Deviation");

	//gotoxy(2, 4);
	for (i = 0; i < 4; i++)
		printf("\n");
	printf("%s", "  +5%");

	//gotoxy(2, 14);
	for (i = 0; i < 10; i++)
		printf("\n");
	printf("  -5%%");

	gotoxy(60, 9);
	printf("Array");

	for (i = 0; i<15; i++)
	{
		gotoxy(6, 2 + i);
		printf("|");
	}

	for (i = 0; i<50; i++)
	{
		gotoxy(7 + i, 9);
		printf("-");
	}

	for (i = 0; i < antal_serier; i++)
	{
		tot_qty += serier[i].totnr;							//Total quantity of resistances
		tot_out += serier[i].outnr;							//Total deviated
		p_out = (100 * (double)tot_out / (double)tot_qty);	//Total deviated (percent)

		//Converting average resistances of each array into an integer
		percent = serier[i].medel / parValue;
		percent = ((1 - percent) * 100);

		percent = (int)round(percent);

		gotoxy(8 + i * 3, 9 + percent);
		printf("o");

	}//for

	gotoxy(20, 20);
	printf("Total resistance-values: %i", tot_qty);

	gotoxy(20, 21);
	printf("Total deviated: %i (%.1lf%%)", tot_out, p_out);		
	//Baked in deviated numbers and percent in one line to save code

	_getch();	//To stop the program for viewing

}//void


int meny_motor(char *alt[], int nr) {
	int i;
	int ch;

	clrscr();
	setcursor(0, 1);
	for (i = 0; i < nr; i++) {
		gotoxy(30, 10 + i);
		puts(alt[i]);
	}

	gotoxy(20, 23);
	printf("Move with the arrow-keys and choose with ENTER!");

	gotoxy(27, 10);
	printf("=> ");
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 0 || ch == 224) {
				ch = _getch();
				if (ch == 80 && wherey() < 9 + nr) {
					gotoxy(wherex() - 3, wherey());
					printf("   ");
					gotoxy(wherex() - 3, wherey() + 1);
					printf("=> ");
				}
				else if (ch == 72 && wherey() > 10) {
					gotoxy(wherex() - 3, wherey());
					printf("   ");
					gotoxy(wherex() - 3, wherey() - 1);
					printf("=> ");
				}
			}
			else if (ch == 13)
				break;
		}
	}
	setcursor(1, 0);
	return wherey() - 9;
}

int main() {
	char *menyalt[] = { "Read measured data",
		"Show statistics",
		"Terminate program" };
	int menyval, slut = 0, antal_serier = 0;
	struct seriepost matserier[20];
	FILE *tsin;

	do {
		menyval = meny_motor(menyalt, 3);
		switch (menyval) {
		case 1:
			tsin = oppna_strom();
			antal_serier = las_data(tsin, matserier);
			fclose(tsin);
			break;
		case 2:
			visa_stat(matserier, antal_serier);
			break;
		case 3:
			slut = 1;
			break;
		}
	} while (!slut);

	return 0;
}

