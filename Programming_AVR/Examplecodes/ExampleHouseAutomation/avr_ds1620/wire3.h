#ifndef _WIRE3_H
#define _WIRE3_H
#include <avr/io.h>

typedef struct
{

	unsigned char dq   : 1;  //D0
    unsigned char clk  : 1;  //D1
    unsigned char rst0 : 1;  //D2
    unsigned char rst1 : 1;  //D3
    unsigned char rst2 : 1;  //D4
    unsigned char rst3 : 1;  //D5
    unsigned char rst4 : 1;  //D6
    unsigned char rst5 : 1;  //D7

} wire3_pins;


//ÄNDRA PORT FÖR BUSSEN HÄR
#define WIRE3_PORT ( *(volatile wire3_pins *) &PORTA)
#define WIRE3_DDR  ( *(volatile wire3_pins *) &DDRA)
#define WIRE3_PIN  ( *(volatile wire3_pins *) &PINA)

void wire3_init(int n_rst);
void wire3_clock_0(void);
void wire3_clock_1(void);
unsigned char  wire3_read8(void);
void wire3_read9(unsigned int *data_out);
void wire3_clock_pulse();
void wire3_rst_0(int no);
void wire3_rst_1(int no);

void wire3_command(unsigned char command);
void wire3_write8(unsigned char data);
void wire3_write9(unsigned int data);

#endif
