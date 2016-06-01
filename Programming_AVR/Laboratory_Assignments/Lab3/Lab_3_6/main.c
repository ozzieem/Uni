#include <avr/io.h>
#include <stdio.h>


int main(void)
{
	FloatMixTest();
	IntTest();		// 39,25 ms
	LongTest();		// 100,88 ms
	FloatTest();	// 103,88 ms
}

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