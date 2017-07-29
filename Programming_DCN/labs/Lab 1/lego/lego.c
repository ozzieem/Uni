/*
**  Namn:            lego.c
**  Version:         mega
**  Syfte:           studera protokollet för Lego RCX
**  Programvara:     AVR-GCC
**  Hårdvara:        MCU (AVR ATmega8515) på STK200-kort monterat på kopplingsbord med LCD, klockfrekvens 8 MHz (kristall på kort)
**                   (ATmega8515 klara max 16 MHz)
**  LED:             10 st LED på MCU
**  LCD:             2-raders display på kopplingsbord, 16 tecken per rad
**  Design:          Jack Pencz
*/


#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>


/* Definitioner för LCD */
#define LINE1 1		// Början av rad 1 på LCD
#define LINE2 168	// Början av rad 2 på LCD


/* Definitioner för UBRR-registret i MCU för asynkron överföring med normal hastighet, inte dubbel */
#define F_CPU 8000000UL      // Använd MCU-frekvensen 8 MHz (kristall på kort)
#define USART_BAUDRATE 2400  // 2400 baud för RCX
#define BAUD_PRESCALE ((F_CPU/(USART_BAUDRATE * 16UL)) - 1) // Bestäm skalfaktor för RCX


/* Globala variabler */
unsigned char add8 = 0;     // Används i SendFrame och GetBattPower för att kunna sända O, O + 8, O, ...


void USART_Init(void)
{
	/* Initiera USART-kretsen i MCU för RS232-kommunikation

	Översikt av MCU-inställningar

    Inställningsordning:
      1. Överföringstyp
      2. Normal eller dubbel hastighet vid asynkron överföring
      3. Bithastighet
      4. Antal databitar
      5. Tillåt (enable) sändning och mottagning
      6. Paritet
      7. Antal stoppbitar

    UCSZ2 UCSZ1 UCSZ0 Databitantal
      0     0     0       5
      0     0     1       6
      0     1     0       7
      0     1     1       8
      1     1     1       9
    Intervallet 100-110 är reserverat.


    UPM1 UPM0 Paritet
      0    0  avstängd
      0    1  reserverad
      1    0  jämn paritet
      1    1  udda paritet


    USBS Stoppbitantal
      0        1
      1        2
    */

	/* Sätt överföringstyp */
	UCSRC &= ~(1 << UMSEL);  // Asynkron överföring
	//UCSRC |= (1 << UMSEL);  // Synkron överföring

	/* Sätt normal eller dubbel hastighet vid asykron överföring */
	UCSRA &= ~(1 << U2X);    // Normal asynkron överföring
	//UCSRA |= (1 << U2X);    // Dubbel hastighet vid asynkronöverföring

	/* Sätt "signalhastighet" med enheten baud (antal signaltillstånd per sekund) */
	UBRRL = BAUD_PRESCALE;         // Ladda de 8 låga bitar i UBRR-registret
	UBRRH = (BAUD_PRESCALE >> 8);  // Ladda de 8 höga bitar i UBRR-registret

	/* Tillåt mottagning och sändning */
	UCSRB = (1 << RXEN) | (1 << TXEN);
    //UCSRB = ((1<<RXEN)|(1<<TXEN)|(1<<RXCIE));  // Endast med servicerutin för mottagningsavbrott

	/* Ramformat (default: 8 databitar, ingen paritet, 1 stoppbit)
	   För kommunikation med RCX: 8 databitar, udda paritet, 1 stoppbit */
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) |(1 << UPM1) | (1 << UPM0);
}


void USART_Flush(void)
{
	/* Rensa RS232-bufferten */

	while (UCSRA & (1<<RXC))  // Rensa bufferten
		UDR;
}


void USART_SendByte(unsigned char u8Data)
{
	/* Sändningsrutin RS232-port */

	while (!(UCSRA & (1<<UDRE)));  // Skicka nästa byte när sändningsbufferten blir tom
	    UDR = u8Data;
}


volatile unsigned char USART_ReceiveByte(void)
{
	/* Mottagningsrutin RS232-port */

	while(!(UCSRA & (1<<RXC)));  // Vänta tills mottagningsbufferten blir fylld
	return UDR;
}


void LCD_Delay(void)
{
	/* LCD-fördröjning anpassad för 8 MHz-klocka
	 *
	 * Eftersom
	 *   #define F_CPU 8000000UL
	 * och inte
	 *   #define F_CPU 1000000UL
	 * stämmer inte fördröjningen helt med antal angivna ms
	 * Testat minumum är värdet 3
	 * Värdet 10 ger marginal
	 */

	_delay_ms(10);
}


void LCD_Intro(unsigned char instr)
{
	/* Radbyte på LCD */
    char  i, j;

    i = instr;
    j = i >> 4;    /* Swappa */
    j = j & 0x0f;

    PORTC = j;
    j = j | 0x10;  /* EN hög och RS låg */
    PORTC = j;
    j = j & 0x0f;  /* EN låg och RS låg */
    PORTC = j;

    LCD_Delay();
    i = i & 0x0f;
    PORTC = i;
     i = i | 0x10;
    PORTC = i;
    i = i & 0x0f;
    PORTC = i;
    LCD_Delay();
}


void LCD_Init(void)
{
    /* Initieringsdata */

    LCD_Delay();
    LCD_Delay();
    LCD_Delay();
    DDRC = 0xFF; // Sätt Port C på STK200-kortet till output för LCD
    PORTC = 0x00;
    LCD_Delay();
    PORTC = 0x03;
    PORTC = 0x13;
    PORTC = 0x03;
    LCD_Delay();
    LCD_Delay();
    PORTC = 0x03;
    PORTC = 0x13;
    PORTC = 0x03;
    LCD_Delay();
    PORTC = 0x03;
    PORTC = 0x13;
    PORTC = 0x03;
    LCD_Delay();
    PORTC = 0x02;
    PORTC = 0x12;
    PORTC = 0x02;
    LCD_Delay();
    LCD_Intro(0x28);
    LCD_Intro(0x0C);
    LCD_Intro(0x01);
    LCD_Intro(0x06);
}


void LCD_CharOut(unsigned char tkn)
{
	/* Visar tecken för tecken på LCD */
    unsigned char  i, j;

    i = tkn;
    j = i >> 4;         /* Swappa */
    j = j & 0x0F;
    j = j | 0x20;       /* RS hög */
    PORTC = j;
    j = j | 0x30;       /* EN hög och RS hög */
    PORTC = j;
    j = j & 0x2F;       /* EN låg och RS hög */
    PORTC = j;

    LCD_Delay();
    i = i & 0x0F;
    i = i | 0x20;       /* RS hög */
    PORTC = i;
    i = i | 0x30;       /* EN hög */
    PORTC = i;
    i = i & 0x2F;       /* EN låg */
    PORTC = i;
    LCD_Delay();
}


void LCD_StrOut(char *tknstr)
{
	/* Visar textsträng på LCD */
    unsigned char  chr;

    while (*tknstr != '\0')
    {
        chr = *tknstr++;
        LCD_CharOut(chr);  // Skicka tecken för tecken till LCD
    }
}


void LCD_Clean(unsigned char line)
{
	/* Rensa LCD-rad */

    LCD_Intro(line);  		         // Gå till början av LCD-raden
    LCD_StrOut("                ");  // Rensa LCD-raden
    LCD_Intro(line);  		         // Gå till början av LCD-raden
}


void LCD_Convert(unsigned char disp)
{
	/* Anpassning av värde för visning på LCD
	   Hexadecimala tal (eller positiva heltal < 256) omvandlas till tecken i en lista
	   Exempel: LCD_Convert(0xA1) visar A1 på LCD
	            LCD_Convert(255) visar FF på LCD
	   Bra för felsökning */
	int lcd_H, lcd_L, i;
	char lcdtext[] = {'\0','\0','\0'};

	/* Dela upp disp i två separata hexadecimala värden */
	lcd_H = (int)disp/16;
	lcd_L = disp - lcd_H*16;

	/* Omvandling till ACSII */
	for(i=0;i<10;i++)  // Urskilj tecknen 0-9
	{
		if(lcd_H == i) lcdtext[0] = i + 48;
	    if(lcd_L == i) lcdtext[1] = i + 48;
	}
	for(i=0;i<6;i++)  // Urskilj tecknen A-F
	{
		if(lcd_H == i+10) lcdtext[0] = i + 65;
		if(lcd_L == i+10) lcdtext[1] = i + 65;
	}

	LCD_StrOut(&lcdtext[0]);  // Skicka tecknen till LCD
}


void MenuDelays(int time)
{
	/* LCD-fördröjning anpassad för 8 MHz-klocka
	 *
	 * Eftersom
	 *   #define F_CPU 8000000UL
	 * och inte
	 *   #define F_CPU 1000000UL
	 * stämmer inte fördröjningen helt med antal angivna ms
	 * Värdet 4 ger marginal
	 */

	if(time == 4)
		_delay_ms(4);  // Lång fördröjning
	else
		_delay_ms(1);  // Kort fördröjning
}


void SendFrame(unsigned char command, unsigned char *parameters)
{
	/* Skapa och sänd en RCX-ram */
    unsigned char i = 0, checksum = 0;

    /* Sätt "+ 8" varannan byte */
    if(add8!= 0)
    {
    	command = command + 0x08;
        add8= 0;  // Jämt antal ramar har strax skickats
    }
    else
    {
    	add8= 1;  // Udda antal ramar har strax skickats
    }

    /* Övning B:1 - Plats för att skicka header och command (operationskod) */
    /* Sänd header */
    USART_SendByte(0x55);
    USART_SendByte(0xFF);
    USART_SendByte(0x00);

    /* Sänd command och dess 1-komplement */
    USART_SendByte(command);
    USART_SendByte(0xFF - command);

    checksum = command;

    /* Sänd parameters */
    while(parameters[i] > 0)  // Sänd parameters och respektive 1-komplement
    {
    	USART_SendByte(parameters[i]);
        USART_SendByte(0xFF - parameters[i]);
        checksum = checksum + parameters[i];
        i++;
    }

    /* Övning B:1 -  Plats för att skicka checksum */
    /* Sänd checksum och dess 1-komplement */

    USART_SendByte(checksum);
    USART_SendByte(0xFF - checksum);

}


void GetBattPower(void)
{
	/* Sänd GET BATTERY POWER */
    unsigned char command, checksum, H1 = 0, H2 = 0, H3 = 0, D1 = 0, D2 = 0, dummy;
    int U;
    char u[8];

    LCD_Clean(LINE2);  		  // Rensa LCD-rad 2 och gå till början av den

    /* Sätt "+ 8" varannan byte */
    if(add8!= 0)
    {
    	command = 0x30 + 0x08;
        add8= 0;  // Jämt antal ramar har strax skickats
    }
    else
    {
        command = 0x30;
        add8= 1;  // Udda antal ramar har strax skickats
    }

    checksum = command;

    /* Övning B:2 - Plats för att skicka header, command (operationskod) och checksum */
    /*Sänd header */

    USART_SendByte(0x55);
    USART_SendByte(0xFF);
    USART_SendByte(0x00);

    /* Sänd command och dess 1-komplement */

    USART_SendByte(command);
    USART_SendByte(0xFF - command);

    /* Sänd checksum och dess 1-komplement */

    USART_SendByte(command);
    USART_SendByte(0xFF - command);

    /* Läs svar */
    wdt_enable(7);             // Slå på watchdog: körbart även om RS232-kommunikation falerar
    H1 = USART_ReceiveByte();  // Läs byte på RS232-port
    H2 = USART_ReceiveByte();  // Läs byte på RS232-port
    H3 = USART_ReceiveByte();  // Läs byte på RS232-port
    while((H1 != 0x55)||(H2 != 0xFF)||(H3 != 0x00))  // Sök efter headern (H1, H2, H3)
    {
    	H1 = H2;
        H2 = H3;
        H3 = USART_ReceiveByte();  // Läs nästa byte på RS232-port
    }
    dummy = USART_ReceiveByte();   // Hoppa över svarskoden code (S)
    dummy = USART_ReceiveByte();   // Hoppa över 1-komplementet (~S)
    D1 = USART_ReceiveByte(); 	   // Läs första data (D1)
    dummy = USART_ReceiveByte();   // Hoppa över 1-komplementet (~D1)
    D2 = USART_ReceiveByte();      // Läs andra data (D2)
    dummy = USART_ReceiveByte();   // Hoppa över 1-komplementet (~D2)
    dummy = USART_ReceiveByte();   // Hoppa över checkcum (C)
    dummy = USART_ReceiveByte();   // Hoppa över 1-komplementet (~C)
    u[7] = dummy;	               // Enbart för att slippa kompileringvarning om dummy
    wdt_disable();  			   // Stäng av watchdog

    /* Beräkna batterispänning och skicka till LCD */
    U = 256*D2 + D1;               // Batterispänningen i mV, [0, 99999]
    u[0] = (int) U/10000;                                     // Tiotals V
    u[1] = (int) (U - u[0]*10000)/1000;                       // Entals V
    u[3] = (int) (U - u[0]*10000 - u[1]*1000)/100;            // Tiondels V
    u[4] = (int) (U - u[0]*10000 - u[1]*1000 - u[3]*100)/10;  // Hundradels V
    if (u[0] != 0)
    	u[0] = u[0] + 48;          // ACSII för tiotals V (Annars, dvs om 0, ersätt med mellanslag)
    else
    	u[0] = ' ';
    u[1] = u[1] + 48;              // ASCII för entals V
    u[2] = '.';                    // Decimalpunkt
    u[3] = u[3] + 48;              // ASCII för tiondels V
    u[4] = u[4] + 48;              // ACSII för hundradels V
    u[5] = ' ';                    // Mellanslag
    u[6] = 'V';                    // Enheten V
    u[7] = '\0';                   // Nulltecken (sista elementet)
    LCD_StrOut(&u[0]);             // Skicka teckensträng till LCD
}


void Menu(void)
{
	/* Programmets huvudmeny */
	unsigned char i = 0, *b;

	/* Evighetsloop nr 2 */
    while(1)
    {
    	while(bit_is_set(PIND,7));             // Om SW.7 har tryckts ner, kort fördröjning
    	    MenuDelays(1);
        i++;   						           // Stega framåt i programmets meny
        switch(i)
        {
            case 1:
            	LCD_Clean(LINE2);  		       // Rensa LCD-rad 2 och gå till början av den
            	LCD_StrOut("Get batt power");  // Skriv alternativet på LCD-rad 2
            	while(bit_is_set(PIND,7))
            	{                              // Så länge SW.7 är satt
            		if(bit_is_clear(PIND,6))
            		{                          // Och, om också SW.6 har varit satt
            			GetBattPower();	       // GET BATTERY POWER
            			MenuDelays(4); 	   // Lång fördröjning
            		}
            	}
            break;

            case 2:
               	LCD_Clean(LINE2);
                LCD_StrOut("Play sound 6");
                while(bit_is_set(PIND,7))
                {
                	if(bit_is_clear(PIND,6))
                	{
                		b = (unsigned char*) "\x06";  // Ljudtyp nr 2
                		SendFrame(0x51, b);           // PLAY SOUND
                	}
                }
            break;

            case 3:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Set motor A pow");
            	while(bit_is_set(PIND,7))
            	{
            		if(bit_is_clear(PIND,6))
            	    {
            			b = (unsigned char*) "\x01\x02\x07";  // Motor A, Level 2, Power 7
            			SendFrame(0x13, b); 	              // SET MOTOR POWER
            			LCD_Clean(LINE2);
            			LCD_StrOut("Motor A is set");
            			MenuDelays(4);
            	    }
            	}
            break;

            case 4:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Motor A on");
            	while(bit_is_set(PIND,7))
            	{
            		if(bit_is_clear(PIND,6))
            	    {
            			b = (unsigned char*) "\x81";  // Modify/turn on motor A
            			SendFrame(0x21, b);           // SET MOTOR ON
            			MenuDelays(4);
            	    }
            	}
            break;

            case 5:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Motor A off");
            	while(bit_is_set(PIND,7))
            	{
            		if(bit_is_clear(PIND,6))
            	    {
            			b = (unsigned char*) "\x41";  // Modify/turn off motor A
            			SendFrame(0x21, b);           // SET MOTOR ON
            			MenuDelays(4);
            	    }
            	}
            break;

            /* Övning B:3 - Plats för att lägga till ljud */
            case 6:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Play Sound 5");
                while(bit_is_set(PIND,7))
                {
                	if(bit_is_clear(PIND,6))
                	{
                		b = (unsigned char*) "\x05";  // Ljudtyp nr 2
                		SendFrame(0x51, b);           // PLAY SOUND
                	}
                }
            break;

            /* Övning B:4 - Plats för att lägga till motor */
            case 7:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Set motor B pow");
            	while(bit_is_set(PIND,7))
            	{
            		if(bit_is_clear(PIND,6))
            	    {
            			b = (unsigned char*) "\x02\x03\x07";  // Motor B, Level 4, Power 8
            			SendFrame(0x13, b); 	              // SET MOTOR POWER
            			LCD_Clean(LINE2);
            			LCD_StrOut("Motor B is set");
            			MenuDelays(4);
            	    }
            	}
            break;

            case 8:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Motor B on");
            	while(bit_is_set(PIND,7))
            	{
            		if(bit_is_clear(PIND,6))
            	    {
            			b = (unsigned char*) "\x81";  // Modify/turn on motor B
            			SendFrame(0x21, b);           // SET MOTOR ON
            			MenuDelays(4);
            	    }
            	}
            break;

            case 9:
            	LCD_Clean(LINE2);
            	LCD_StrOut("Motor B off");
            	while(bit_is_set(PIND,7))
            	{
            		if(bit_is_clear(PIND,6))
            	    {
            			b = (unsigned char*) "\x41";  // Modify/turn off motor B
            			SendFrame(0x21, b);           // SET MOTOR ON
            			MenuDelays(4);
            	    }
            	}
            break;

            default:
            	LCD_Clean(LINE2);  		   // Rensa LCD-rad 2 och gå till början av den
            	LCD_StrOut("Press SW.7");  // Skriv (igen) på LCD-rad 2
        	    i = 0;                     // Nollställ valt case
        }
    }
}


int main(void)
{
	/* Initieringar */
    USART_Init();   // Initiera USART
    USART_Flush();  // Rensa RS232-bufferten
    LCD_Init();     // Initiera LCD
                    // Använd Port A på STK200-kortet för NC
    DDRB = 0xFF;    // Använd Port B på STK200-kortet för LED:s (data output, obs STK200 tre olika kontakttyper)
                    // Använd Port C på STK200-kortet för LCD (data output, sätts i LCD_Init()
    DDRD = 0x00;    // Använd Port D på STK200-kortet för switcharna (data input)
                    // Använd Port E på STK200-kortet för NC

     /* Visa text på LCD */
     LCD_Clean(LINE1);  		  // Rensa LCD-rad 1 och gå till början av den
     LCD_StrOut("LEGO RCX I/O");  // Skriv titeln på LCD-rad 1
     LCD_Clean(LINE2);  		  // Rensa LCD-rad 2 och gå till början av den
     LCD_StrOut("Press SW.7");    // Skriv på LCD-rad 2


     /* Evighetsloop nr 1 */
     while(1)
     {
    	 Menu(); 		 // Hantera programmets meny
         MenuDelays(1);  // Kort fördröjning
     }
     return 0;
}








