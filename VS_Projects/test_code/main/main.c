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
Antag att följande deklaration har gjorts
int i = 1 6 3 ;
Vilket värde antar i efter följande tilldelningsats:
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
Om följande deklaration gäller
#define RXC 6
vad beräknas då följande till
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
I ett C-program nns följande kodfragment:
long x ;
unsigned char b ;
x = 0x8ECEE1C1 ;
b =  ( ( ( unsigned char ) &x )+1) ;
Vilket värde får variabeln b? Antag att little-endian lagring av data. Svaret ges i
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
Antag att följande pekardeklaration gäller:
long p=0X01D4 ;
Vilken adress i minnet accessas vid följande operation:
(p+11)
Antag att int är på 2 bytes, long och float på 4 bytes och double på 8 bytes. Svara
med det hexadecimala värdet med fyra siffror.

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

