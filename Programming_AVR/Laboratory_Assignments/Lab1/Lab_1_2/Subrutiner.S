
;;;--- I/O-adresses for Port D ---
#define PIND	0x10
#define DDRD	0x11
#define PORTD	0x12

;;;--- I/O-adresses for Port C ---
#define PINC	0x13
#define DDRC	0x14
#define PORTC	0x15

;;;--- I/O-adresses for Port B ---
#define PINB	0x16
#define DDRB	0x17
#define PORTB	0x18

;;;--- I/O-adresses for Port A ---
#define PINA	0x19
#define DDRA	0x1A
#define PORTA	0x1B

;;;; CHECK INSTRUCTION MANUAL FOR SPECIFIC INSTRUCTIONS

        .data

lamps:	.byte 0		;;   unsigned char lamps = 0;

        .text
        .global init_func
         
init_func:
		;; DDRA = 0x00
		LDI		R20, 0x00
		OUT		DDRA, R20

		;; DDRB = 0xFF;
		LDI		R20, 0xFF
		OUT		DDRB, R20
		
        RET

        .text
        .global loop_func

loop_func:
		
		;; PORTB = PINA 
		IN		R20, PINA
		OUT		PORTB, R20
	
        RET
 