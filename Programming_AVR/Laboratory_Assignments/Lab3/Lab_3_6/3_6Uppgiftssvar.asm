UPPGIFT 3_6a___________________________________________
	22 mikrosekunder

UPPGIFT 3_6b___________________________________________
Skillnad mellan volatile och utan

Med volatile:
{
	gXi = 20;
0000003E  LDI R24,0x14		Load immediate 
0000003F  LDI R25,0x00		Load immediate 
00000040  STS 0x0065,R25		Store direct to data space 
00000042  STS 0x0064,R24		Store direct to data space 
	gYi = 30;
00000044  LDI R24,0x1E		Load immediate 
00000045  LDI R25,0x00		Load immediate 
00000046  STS 0x0061,R25		Store direct to data space 
00000048  STS 0x0060,R24		Store direct to data space 
	gRi = gXi * gYi;
0000004A  LDS R20,0x0064		Load direct from data space 
0000004C  LDS R21,0x0065		Load direct from data space 
0000004E  LDS R18,0x0060		Load direct from data space 
00000050  LDS R19,0x0061		Load direct from data space 
00000052  MUL R20,R18		Multiply unsigned 
00000053  MOVW R24,R0		Copy register pair 
00000054  MUL R20,R19		Multiply unsigned 
00000055  ADD R25,R0		Add without carry 
00000056  MUL R21,R18		Multiply unsigned 
00000057  ADD R25,R0		Add without carry 
00000058  CLR R1		Clear Register 
00000059  STS 0x0063,R25		Store direct to data space 
0000005B  STS 0x0062,R24		Store direct to data space 
}

Utan volatile:
{
	gXi = 20;
0000003E  LDI R24,0x14		Load immediate 
0000003F  LDI R25,0x00		Load immediate 
00000040  STS 0x0065,R25		Store direct to data space 
00000042  STS 0x0064,R24		Store direct to data space 
	gYi = 30;
00000044  LDI R24,0x1E		Load immediate 
00000045  LDI R25,0x00		Load immediate 
00000046  STS 0x0061,R25		Store direct to data space 
00000048  STS 0x0060,R24		Store direct to data space 
	gRi = gXi * gYi;
0000004A  LDI R24,0x58		Load immediate 
0000004B  LDI R25,0x02		Load immediate 
0000004C  STS 0x0063,R25		Store direct to data space 
0000004E  STS 0x0062,R24		Store direct to data space 
}

Det verkar som om utan volatile sker inte beräkningen i assembly, utan värdet läggs direkt in i registret pga optimering.

UPPGIFT3_6c___________________________________________ 

int main(void)
{
	IntTest();		// 39,25 ms
	LongTest();		// 100,88 ms
	FloatTest();	// 103,88 ms
}

void IntTest()
{
	volatile int gXi = 0x0040, gYi = 0x0020, gRi = 0;
	gRi = gXi + gYi;	//1,75 ms
	gRi = gXi * gYi;	//2,75 ms
	gRi = gXi / gYi;	//28,5 ms
}

void LongTest()
{
	volatile long gXi = 0x0040L, gYi = 0x0020L, gRi = 0;
	gRi = gXi + gYi;	// 3,50 ms
	gRi = gXi * gYi;	// 12,13 ms
	gRi = gXi / gYi;	// 77,25 ms
}

void FloatTest()
{
	volatile float gXi = 20.0, gYi = 30.0, gRi = 0;
	gRi = gXi + gYi;	// 15,38 ms
	gRi = gXi * gYi;	// 18,50 ms
	gRi = gXi / gYi;	// 62,00 ms
}

UPPGIFT3_6d___________________________________________

void FloatMixTest()
{
	volatile float gFi = 1.5;
	volatile float gRi = 0;

	// float = float * int;
	volatile int gXi = 0x0040;
	gRi = gFi * gXi;	// 26,25 ms

	// float = float * long;
	volatile long gLi = 0x0020;
	gRi = gFi * gLi;	// 25,50 ms

	// float = float * float;
	gRi = gFi * gFi;	// 20,88 ms
}

UPPGIFT3_6e___________________________________________
Denna simulering visar att datatypen int är snabbast att beräkna medan long och float kommer efter i beräkningstid. Addition är snabbare att beräkna, multiplikation är ungefär lika snabb som addition medan division är långsammast. 
Simuleringen i förra uppgiften visade också att det inte är så stora skillnader att utföra aritmetiska beräkningar mellan olika datatyper då det bara skiljde några mikrosekunder. Generellt sett verkar det som om float är den datatypen som tar längst tid att utföra beräkningar med. Detta kan bero på att flera instruktioner måste utföras i assembly för att göra samma beräkning, jämfört med till exempel int. Long har 64 bitar, medan float har 32-bitar, likadant som int, men skillnaden är att float har "decimalbitar" som kan försvåra beräkningarna någorlunda.
