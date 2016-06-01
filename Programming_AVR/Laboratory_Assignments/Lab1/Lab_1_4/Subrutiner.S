
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

;;;--- Variables ---
        .data

;;;-- Global variables

;;;--- subrutin init_func ---
        .text
        .global init_func
         
init_func:

		LDI R20, 0xFF
		OUT DDRB, R20
		CLT 

        RET

;;;--- subrutin loop_func ---
        .text
        .global loop_func

loop_func:

		BLD		R21, 7
		BST		R20, 6		
		ROL		R21	
		ROL		R20

		OUT PORTB, R20


		RET