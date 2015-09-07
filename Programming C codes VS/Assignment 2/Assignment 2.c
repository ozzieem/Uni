#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main(void){


	int s, h, i; /*Starting number, Jump number, for-loop-var*/
	float g; /* Difficulty */

	printf("Enter the startnumber: ");
	scanf("%d", &s);

	while (s != 0){

		if (s > 0){
			float t = 0, min = 10, max = 0, p = 0; /*Total, max-value, min-value*/

			printf("Enter the jump-number: ");
			scanf("%d", &h);
			printf("Enter the difficulty: ");
			scanf("%f", &g);
			printf("\n");

			for (i = 1; i < 8; ++i){ /* Judging points */
				printf("Judgescore %d: ", i); /*Puts in i as the number for the judgingpoints*/
				scanf("%f", &p);
				if (p >= 0 && p <= 10){
					t = t + p; /*Total score*/
					if (p >= max) /*Assigning appropriate min/max value*/
						max = p;
					else if (p <= min)
						min = p;
				}
				else if (p < 0 || p > 10){ /* If the number is not 0-10*/
					printf("Enter a value between 0-10: ");
					printf("\nJudgescore %d: ", i);
					scanf("%f", &p);
					if (p >= 0 && p <= 10){
						t = t + p; /*Total score*/
						if (p >= max) /*Assigning appropriate min/max value*/
							max = p;
						else if (p <= min)
							min = p;
					}
					else{
						printf("Enter a value between 1-10: ");
						printf("\nJudgescore %d: ", i--);
						scanf("%f", &p);
					}
				}

			}/*for*/

			printf("\nJump-score: %.2f\n", (((t - (min + max)) / 5)*(3 * g))); /*Calculates everything together*/
			printf("\nPress any key to enter a new jump!\n");
			_getch();

		}/*else if*/

		printf("\nEnter the startnumber: ");
		scanf("%d", &s);

	} /*while*/

	return 0;

} /*main*/
