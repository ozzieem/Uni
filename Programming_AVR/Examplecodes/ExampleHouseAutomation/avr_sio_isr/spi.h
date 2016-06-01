#ifndef _SPI_H
#define _SPI_H
#include <avr/io.h>

typedef struct
{

	unsigned char si     : 1;  //D0
    unsigned char clk    : 1;  //D1
    unsigned char unused : 4;  //D2-D5
    unsigned char cs_n   : 1;  //D6
    unsigned char so     : 1;  //D7

} spi_pins;


//ÄNDRA PORT FÖR BUSSEN HÄR
#define SPI_PORT ( *(volatile spi_pins *) &PORTA)
#define SPI_DDR  ( *(volatile spi_pins *) &DDRA )
#define SPI_PIN  ( *(volatile spi_pins *) &PINA )

void spi_init();
void spi_clock_pulse();
void spi_clock_1(void);
void spi_clock_0(void);
void spi_cs_n(int value);

#endif
