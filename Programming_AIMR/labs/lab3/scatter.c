#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *f = fopen("scatterfile.txt", "a");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	int x = 0;
	int y = 0;
	int x_max = 100;
	int y_max = 100;

	for(int i = 0; i <= 100; i++) {
		fprintf(f, "%d %d\n", x, y)
		printf("%d %d\n", x, y);
	}

	fclose(f);
}
