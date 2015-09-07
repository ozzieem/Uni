/* Ishodstud.c -- 2014-02-26 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "MSViscon.h"

#define ESC 27

struct lag {
	char namn[20];
	int gjorda;
	int inslappta;
	int poang;
};

int main(void) {
	struct lag temp, serie[] = {
		{ "Bryn\204s", 0, 0, 0 },
		{ "Djurg\206rden", 0, 0, 0 },
		{ "Fr\224lunda", 0, 0, 0 },
		{ "F\204rjestad", 0, 0, 0 },
		{ "HV 71", 0, 0, 0 },
		{ "Link\224ping", 0, 0, 0 },
		{ "Lule\206", 0, 0, 0 },
		{ "MODO", 0, 0, 0 },
		{ "R\224gle", 0, 0, 0 },
		{ "Skellefte\206", 0, 0, 0 },
		{ "S\224dert\204lje", 0, 0, 0 },
		{ "Timr\206", 0, 0, 0 }
	};


	int i, j, home, away, row;

	srand((unsigned)time(NULL)); //Seed the random number generator

	do {
		clrscr();

		row = 0;

		//1. Generating and adding numbers to teams

		for (i = 0; i<12; i += 2){							//Loop through all the 12 teams with a jump of 2, since (i+1) calculates the two teams who play against eachother

			home = rand() % 9;
			serie[i].gjorda = serie[i].gjorda + home;						//Give serie[i] a random goal number between 0-8 from home-variable
			away = rand() % 9;
			serie[i + 1].gjorda = serie[i + 1].gjorda + away;				//Give serie[i+1] a random goal number between 0-8 from away-variable

			serie[i].inslappta = serie[i].inslappta + away;			//Give serie[i].inslappta as many goals as the opposing serie[i+1] did
			serie[i + 1].inslappta = serie[i + 1].inslappta + home;		//Give serie[i+1].inslappta as many goals as the opposing serie[i] did

			gotoxy(0, row);
			printf("%s", serie[i].namn);
			gotoxy(15, row);
			printf("- %s", serie[i + 1].namn);
			gotoxy(32, row);
			printf("%d", home);
			gotoxy(33, row);
			printf("-%d", away);

			row++;

			if (home > away)										//If serie[i] did more goals than serie[i+1], give serie[i] 3 points
				serie[i].poang = serie[i].poang + 3;
			else if (home < away)									//If not, give serie[i+1] 3 points instead
				serie[i + 1].poang = serie[i + 1].poang + 3;
			else{													//Tie gives both serie[i] and serie[i+1] 1 point
				serie[i].poang = serie[i].poang + 1;
				serie[i + 1].poang = serie[i + 1].poang + 1;
			}
		}

		//2. Sorting by points, goal-difference and goals made

		for (i = 0; i<12; i++){
			for (j = i; j<12; j++){
				if (serie[i].poang < serie[j].poang){				//If points of serie[i] < points of [serie[j], sort by points
					temp = serie[i];
					serie[i] = serie[j];
					serie[j] = temp;
				}
				else if (serie[i].poang == serie[j].poang){			//If serie[i] and serie[j] has the same amount of points, sort by goal-difference
					if ((serie[i].gjorda - serie[i].inslappta) < (serie[j].gjorda - serie[j].inslappta)){		
						temp = serie[i];
						serie[i] = serie[j];
						serie[j] = temp;
					}
				}
				else if ((serie[i].poang < serie[j].poang) && ((serie[i].gjorda - serie[i].inslappta) < (serie[j].gjorda - serie[j].inslappta))){
					if (serie[i].gjorda < serie[j].gjorda){
						temp = serie[i];							//If serie[i] and serie[j] has equal amounts of points and goal-diff, sort by goals made
						serie[i] = serie[j];										
						serie[j] = temp;
					}
				}
			}
		}

		//3. Printing out final info in a table

		printf("\n");

		for (int i = 0; i < 12; i++){	//I tried to make this loop its own function to print out the results, but I realised that it would probably break the KISS-rule

			gotoxy(0, i + 7);
			printf("%s", serie[i].namn);
			gotoxy(18, i + 7);
			printf("%d - ", serie[i].gjorda);
			gotoxy(23, i + 7);
			printf("%d", serie[i].inslappta);
			gotoxy(32, i + 7);
			printf("%d", serie[i].poang);
		}

		gotoxy(10, 23);
		printf("This program is originally constructed by Gunnar Joki.");
		gotoxy(10, 24);
		printf("Press any key to play again! (ESC to exit)");
	} while (_getch() != ESC);

	return 0;
}



/*
Function for printing out stats:

void print_table(struct lag table[], int table_size) {
	for (int i = 0; i < table_size; i++) {
		gotoxy(0, i + 7);
		printf("%s", table[i].namn);
		gotoxy(18, i + 7);
		printf("%d - ", table[i].gjorda);
		gotoxy(23, i + 7);
		printf("%d", table[i].inslappta);
		gotoxy(32, i + 7);
		printf("%d", table[i].poang);
	}
}

Call with:

print_table(serie, sizeof(serie) / sizeof(serie[0]));

*/