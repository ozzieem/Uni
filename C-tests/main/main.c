#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#if 0

int main()
{
	int a = 30009, b = 3973;
	char c = 35;
	int *p;
	p = (int*)&c;


//3973 - 3864 = 109

}

#endif

#if 0
/*
Antag att f�ljande deklaration har gjorts
int i = 1 6 3 ;
Vilket v�rde antar i efter f�ljande tilldelningsats:
i = i << 5 ;
Ange svaret som ett decimalt tal.
*/
int main()
{
	int i = 231;
	printf("%d\n", i);
	i = i << 6;
	printf("%d\n", i);
	_getch();
}
#endif

#if 0
/*
Om f�ljande deklaration g�ller
#define RXC 6
vad ber�knas d� f�ljande till
(1 << RXC)
Ange svaret som ett decimalt tal.
*/
#define RXC 4
int main()
{
	int i = (1 << RXC);
	printf("%d", i);
	_getch();
}
#endif

#if 0
/*
I ett C-program nns f�ljande kodfragment:
long x ;
unsigned char b ;
x = 0x8ECEE1C1 ;
b =  ( ( ( unsigned char ) &x )+1) ;
Vilket v�rde f�r variabeln b? Antag att little-endian lagring av data. Svaret ges i
hexadecimala talsystemet.
*/
int main()
{
	long x;
	unsigned char b;

	x = 0x8ECEE1C1;
//x = 0xB98DC3F8;
	b = *((unsigned char *)&x + 1);

	printf("%x", b);

	_getch();
}
#endif

#if 0
/*
Antag att f�ljande pekardeklaration g�ller:
long p=0X01D4 ;
Vilken adress i minnet accessas vid f�ljande operation:
(p+11)
Antag att int �r p� 2 bytes, long och float p� 4 bytes och double p� 8 bytes. Svara
med det hexadecimala v�rdet med fyra siffror.

long = 4 bytes
11*4 = 44(10)
44(10) = 2C(16)
0x01D4 + 0x002C = 0x0200
*/
int main()
{
	float f = 10.5;
	float *p = &f;
	printf("*p = %p\n", &*p);
	
	*p = *(p + 11);
	printf("*(p + 11)=");
	printf("%p", &*(p+11));

	_getch();
}

#endif

