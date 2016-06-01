#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "io_bit_fields.h"
#include "io_usart_isr.h"
#include "spi.h"
#include "eeprom.h"




void command_ddra();
void command_ddrb();
void command_pa();
void command_pb();

/**
 *  Convert alphabetical letters to upper case
 */
void string_to_upper(char *s)
{
	while ( *s != '\0')
	{
		if ( ('a' <= *s) && (*s <= 'z') )
		{
			*s = *s + 'A'-'a';
		}
		s++;
	}
}


unsigned int v=0;
int  pa;
int  pb;

char *word;
char *word2;
char *brk;
char *delim = " ,-\n\r";

char s[128];
char vdata[32];
char vi;
int address=0;
int data=0;

int main()
{
	spi_init();
	eeprom_write_enable();

	io_usart_isr_init(9600, 8000000);
	io_usart_isr_print("avr_sio_isr - 1\r\n");

	asm("	SEI		");


	while ( 1 )
	{

		if ( io_usart_isr_event_termination_character('\n') )
		{
			io_usart_isr_readString(s, 127, '\n');

  			word = strtok_r (s,delim, &brk);
			string_to_upper(word);

			if (word != NULL)
			{	
							     if ( strcmp_P(word,PSTR("DDRA"))   == 0 ) 	command_ddra();
							else if ( strcmp_P(word,PSTR("PA"))     == 0 ) 	command_pa();
							else if ( strcmp_P(word,PSTR("DDRB"))   == 0 ) 	command_ddrb();
							else if ( strcmp_P(word,PSTR("WR"))     == 0 ) 	
							{
								word = strtok_r (NULL, delim, &brk);
								if ( word != NULL )
									sscanf(word,"%x", &address);
								word = strtok_r (NULL, delim, &brk);
								if ( word != NULL )
									sscanf(word,"%x", &data);
								eeprom_write(address,data);
								sprintf(s,"wr %04x: %02x\n\r", address, data);
								io_usart_isr_print(s);
		
							}
							else if ( strcmp_P(word,PSTR("RD"))     == 0 ) 	
							{
								word = strtok_r (NULL, delim, &brk);
								if ( word != NULL )
									sscanf(word,"%x", &address);
								data = eeprom_read(address);
								sprintf(s,"rd %04x: %02x\n\r", address, data);
								io_usart_isr_print(s);
							}
							else if ( strcmp_P(word,PSTR("SR"))     == 0 ) 	
							{
								word = strtok_r (NULL, delim, &brk);
								if ( word != NULL )
									sscanf(word,"%x", &address);
								data = eeprom_read_sr();
								sprintf(s,"sr %02x\n\r", data);
								io_usart_isr_print(s);
							}
							else if ( strcmp_P(word,PSTR("RDALL"))     == 0 ) 	
							{
								int i;
								for (i=0; i<1024; i++)
								{
									if ( (i % 32) == 0 )
									{
										io_usart_isr_print("\n\r");
										sprintf(s," %04x: ",i);
										io_usart_isr_print(s);
									}
									data = eeprom_read(i);
									sprintf(s," %02x ",data);
									io_usart_isr_print(s);
									
								}
							}
							else if ( strcmp_P(word,PSTR("WRVECT"))     == 0 ) 	
							{
								word = strtok_r (NULL, delim, &brk);
								if ( word != NULL )
									sscanf(word,"%x", &address);
								vi=0;
								do
								{
									word = strtok_r (NULL, delim, &brk);
									
									if ( word != NULL );
									{
										if ( sscanf(word,"%x", &data) == 1)
										{
											vdata[(int)vi]=data;
											vi++;
										}
									}
								}
								while ( word != NULL );

								eeprom_write_vector(address, vdata, vi);
								sprintf(s,"WRTEST %d bytes \n\r", (int) vi);
								io_usart_isr_print(s);
		
							}
							else
							{
								//asm("CLI");
								//Test
								io_usart_isr_print("a0123456789b0123456789c0123456789d0123456789e0123456789f0123456789");
								//asm("SEI");
							}

			}
		}
	}//while

	return 0;
}



/**
  * Print a string on the serial port.
  */

void print_reply(char *msg )
{
	sprintf(s,"Reply: %s\n\r", msg);
	io_usart_isr_print(s);
}

/**
 * Setup for PORTA.
 */
void command_ddra()
{
	word = strtok_r (NULL, delim, &brk);
	if ( word != NULL )
	{
		if ( strcmp(word,"?") == 0 )
		{
			pa = DDRA;
			sprintf(s,"DDRA %d\n", pa);
			io_usart_isr_print(s);
		}
		else
		{
			sscanf(word,"%d", &pa);
			DDRA = pa;	
		}
	}
}


/**
 * Setup for DDRB
 */
void command_ddrb()
{
	word = strtok_r (NULL, delim, &brk);
	if ( word != NULL )
	{
		if ( strcmp(word,"?") == 0 )
		{
			pa = DDRB;
			sprintf(s,"DDRB %d\n", pa);
			io_usart_isr_print(s);
		}
		else
		{
			sscanf(word,"%d", &pa);
			DDRB = pa;	
		}
	}
}


/**
 * Command for PORTA
 */
void command_pa()
{
	
	word = strtok_r (NULL, delim, &brk);
	if ( word != NULL )
	{
		if ( strcmp(word,"?") == 0 )
		{
			pa = PINA;
			sprintf(s,"PA %d\n", pa);
			io_usart_isr_print(s);
		}
		else
		{
			sscanf(word,"%d", &pa);
			PORTA = pa;	
		}
	}
}

/**
 * Command for PORTB
 */
void command_pb()
{
	
	word = strtok_r (NULL, delim, &brk);
	if ( word != NULL )
	{
		if ( strcmp(word,"?") == 0 )
		{
			pa = PINB;
			sprintf(s,"PB %d\n", pa);
			io_usart_isr_print(s);
		}
		else
		{
			sscanf(word,"%d", &pa);
			PORTB = pa;	
		}
	}
}



