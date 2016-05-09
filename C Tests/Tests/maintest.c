#include <stdio.h>
#include <conio.h>

const char morse_codes[10][6] =
{
	"_____", ".____",
	"..___", "...__",
	"...._", ".....",
	"_....", "__...",
	"___..", "_____."
};

int main()
{
	int arr_size = sizeof(morse_codes) / sizeof(*morse_codes);
	printf("Allocated size of array: %d\n", sizeof(morse_codes));
	printf("Size of element in array: %d\n", sizeof(*morse_codes));
	printf("Elements in array: %d\n\n", arr_size);

	_getch();
}

#if 0
int main()
{
	const char morse_codes[10][10] =
	{
		"-----",
		".----",
		"..---",
		"...--",
		"....-",
		".....",
		"-....",
		"--...",
		"---..",
		"----."
	};

	while (1)
	{
		int numb;
		printf("Enter number to print morse code: ");
		scanf_s("%d", &numb);

		if (numb == -1)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
					printf("%c", morse_codes[i][j]);
				printf("\n");
			}
		}
		else
		{
			printf("Number %d in morse code is: ", numb);
			for (int j = 0; j < 5; j++)
				printf("%c", morse_codes[numb][j]);
		}

		printf("\n");
	}

	_getch();
}

#endif