#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void ovning3_A();
void ovning3_B();
void ovning3_C();
void ovning6_A();
void ovning6_B();
void ovning6_C();
void ovning6_D();
void ovning6_E();
void ovning6_F();

void struct_fraction();
void random_password();
void const_pointer_test();

#if 1

int main()
{
	//ovning3_A();
	//ovning3_B();
	//ovning3_C();
	//ovning6_A();
	//ovning6_B();
	//ovning6_C();
	//ovning6_D();
	//ovning6_E();
	//ovning6_F();
	//struct_fraction();
	//random_password();
	const_pointer_test();


	_getch();
}

#endif

void const_pointer_test()
{
	int const a = 0;
	int* p = &a;

	printf("a = %d\n", a);
	printf("*p = %d\n", *p);
	printf("p = %p\n\n", p);

	*p = 20;

	printf("a = %d\n", a);
	printf("*p = %d\n", *p);
	printf("p = %p\n", p);
}

void ovning3_A()
{
	int tal;

	printf("Ange tal:");
	scanf_s("%d", &tal);

	if (tal % 2 == 0)
	{
		printf("Tal är jämnt \n");
	}
	else
	{
		printf("Tal är udda \n");
	}
}


void ovning3_B()
{
	int vinkel;

	printf("Ange vinkel:");
	scanf_s("%d", &vinkel);

	if (vinkel == 90)
	{
		printf("Vinkeln är rät \n");
	}
	else if (vinkel < 90)
	{
		printf("Vinkeln är spetsig \n");
	}
	else if (vinkel > 90)
	{
		printf("Vinkeln är trubbig \n");
	}
}

void ovning3_C()
{
	float tal;

	printf("Ange ett reelt tal:");
	scanf_s("%f", &tal);

	if (tal < 0)
	{
		printf("Får inte vara negativ \n");
	}
	else
	{
		tal = sqrt(tal);
		printf("%.3f", tal);
	}
}

void ovning6_A()
{
	FILE* fp;
	fopen_s(&fp, "./files/reelatal.txt", "w");

	double reeltal = 1;
	do
	{
		printf("Skriv tal (0 avslutar): ");
		scanf_s("%lf", &reeltal);

		fprintf(fp, "%.2f\n", reeltal);
	}
	while (reeltal != 0.0);

	fclose(fp);
}

void ovning6_B()
{
	FILE* fp;
	fopen_s(&fp, "./files/reelatal.txt", "r");

	auto antal_tal = 0;
	float medelvarde = 0, tal;
	while (fscanf_s(fp, "%f", &tal) != EOF)
	{
		printf("%f + \n", tal);
		medelvarde += tal;
		antal_tal++;
	}

	printf("Antal tal: %d\n", antal_tal);
	printf("Medelvärde av reela tal i fil: %f", medelvarde / antal_tal);
}

void ovning6_C()
{
	FILE* fp;
	fopen_s(&fp, "./files/semikolon.txt", "r");

	auto antal_semikolon = 0;
	char semi_c;
	while (fscanf_s(fp, "%c", &semi_c) != EOF)
	{
		if (semi_c == ';')
		{
			printf("%c", semi_c);
			antal_semikolon++;
		}
	}

	printf("Antal semikolon: %d\n", antal_semikolon);
}

void ovning6_D()
{
	FILE* fp;
	fopen_s(&fp, "./files/personnamn.txt", "r");

	auto antal_namn = 0;
	char namn[10];
	while (fgets(namn, 10, fp) != NULL)
	{
		antal_namn++;
		printf("%d - %s", antal_namn, namn);
	}
}

void ovning6_E()
{
	FILE* fp;
	fopen_s(&fp, "./files/tarningskast.dat", "wb");
	srand(time(NULL));

	for (auto i = 0; i < 500; i++)
	{
		int tarningskast = rand() % 6 + 1;
		fwrite(&tarningskast, sizeof(tarningskast), 1, fp);
	}

	fclose(fp);

	printf("Tärningskast skrivna till fil");
}

void ovning6_F()
{
	FILE* fp;

	fopen_s(&fp, "./files/tarningskast.dat", "rb");

	float medelvarde = 0;
	int antal_tarningar = 0;
	while (antal_tarningar < 500)
	{
		int tarning;
		fread(&tarning, sizeof(int), 1, fp);

		medelvarde += tarning;
		antal_tarningar++;
	}
	fclose(fp);

	printf("Medelvärde av tärningar %f", medelvarde / antal_tarningar);
}


void struct_fraction()
{
	struct rtal
	{
		int taljare;
		int namnare;
	} tal1, tal2, summa;

	printf("Skriv ett bråktal a / b: ");
	scanf_s("%d/%d", &tal1.taljare, &tal1.namnare);

	printf("Skriv annat bråktal a / b: ");
	scanf_s("%d/%d", &tal2.taljare, &tal2.namnare);

	summa.taljare = tal1.taljare * tal2.namnare + tal2.taljare * tal1.namnare;
	summa.namnare = tal1.namnare * tal2.namnare;

	printf("%d/%d + %d/%d = %d/%d\n",
	       tal1.taljare, tal1.namnare,
	       tal2.taljare, tal2.namnare,
	       summa.taljare, summa.namnare);
}

void random_password()
{
	srand((unsigned)time(NULL));

	while (1)
	{
		int pass_length = 0;

		printf("Password length:");
		scanf_s("%d", &pass_length);

		char* password = malloc(pass_length);

		for (int i = 0; i < pass_length; i++)
		{
			password[i] = rand() % 126 + 33;
		}
		for (size_t i = 0; i < pass_length; i++)
		{
			printf("%c", password[i]);
		}

		printf("\n");
		free(password);
		_getch();
	}
}

