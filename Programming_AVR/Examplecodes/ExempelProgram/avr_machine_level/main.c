#include <stdio.h>
#include <avr/io.h>
#include "io_bit_fields.h"

void wait_milliseconds(int); //Prototype
int add2(int a, int b);
long add4(long a, long b);
unsigned char RFac(unsigned char n);
unsigned char IFac(unsigned char n);

volatile int i1=0x1234;
volatile int i2=0x8765;
volatile int i3;
volatile long l1=0x12345678L;
volatile long l2=0x87654321L;
volatile long l3;
volatile unsigned char rfc,ifc; //Fakultetsberäkningar

typedef struct
{
	long long x,y,z,u,v; //Hur många bytes?
} data;

volatile data sData ={0x1011121314151617, 0x2021222324252627,  0x2021222324252627,  0x2021222324252627};

__attribute__((noinline))
data dataF3( volatile data d)
{
	d.x=0;
	return d;
}


//VAD HÄNDER INNAN VI KOMMER TILL main <-> CSTARTUP
//  Fråga: Vad görs innan vi kommer till main?
int main()
{
	data d = dataF3(sData);
	
	//VAD HÄNDER PÅ STACKEN
	// Fråga: Hur får StackPekaren SP sitt initiala värde?
    // Fråga: Vad händer på stacken?

	i3 = add2(i1,i2);

	l3 = add4(l1,l2);

	printf("%d+%d=%d", i1, i2, i3 );

	DDRB=0xFF;

	// VARFÖR volatile
	//volatile unsigned char * ptr = &PORTB; //FALL 1
	unsigned char * ptr = &PORTB;      //FALL 2

	*ptr = 0x30;
	*ptr = 0x32;
	*ptr = 0x30;


	//OPTIMERANDE KOMPILATOR: Blir det någon skillnad i maskinkod?
	*ptr = 0xFF ^ *ptr; // FALL 1
	//*ptr = 0x0F ^ *ptr;   // FALL 2
	//wait_milliseconds(500);	
	
	
	//REKURSIV FUNKTION
	// Optimeringsgrad Os,O3,O2 ger iterativ lösning
	//                 O1 ger rekursiv lösning
	//Fråga 1: Vad händer på stacken?
	//Fråga 2: När är det att föredra en iterativ lösning?


	rfc = RFac(5);
	ifc = IFac(5);

	printf("RFac(5)=%d, IFac(5)=%d\n\r)", rfc, ifc);
	
	return 0;
}
