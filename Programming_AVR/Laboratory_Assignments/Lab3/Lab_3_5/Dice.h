#ifndef DICE_H_
#define DICE_H_

typedef struct 
{
	unsigned char diceTwo : 3;		//Bit 0-2
	unsigned char unusedOne : 1;	//Bit 3 används ej
	unsigned char diceOne : 3;		//Bit 4-6
	unsigned char unusedTwo : 1;	//Bit 7 används ej.
} diceRegister; 

#define bDicePORT (*(volatile diceRegister *) &PORTB)
#define bDiceDDR (*(volatile) diceRegister *) &DDRB)
#define bDicePIN (*(volatile) diceRegister *) &PINB)

#endif