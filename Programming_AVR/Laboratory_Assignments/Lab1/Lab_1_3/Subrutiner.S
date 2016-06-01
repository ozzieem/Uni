
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
;;   unsigned char lamps = 0;
lamps:	.byte 0

;;;--- subrutin init_func ---
        .text
        .global init_func
         
init_func:
		;; DDRA = 0x00
		LDI		R20, 0x00
		OUT		DDRA, R20

		;; DDRB = 0xFF;
		LDI		R20, 0xFF
		OUT		DDRB, R20
		
		;; PORTB = 0xFF;
		OUT		PORTB, R20
        RET

;;;--- subrutin loop_func ---
        .text
        .global loop_func

loop_func:
		
		;; R20 = PINA & 0x08
		IN R20, PINA
		COM R20
		ANDI R20, 0b00001000

		;; R20 = R20 >> 3
		LSR R20
		LSR R20
		LSR R20

		; R21 = PORTB & 0xFE
		IN R21, PORTB
		COM R21
		ANDI R21, 0xFE

		OR R20, R21		; R20 = R20 | R21
		COM R20
		OUT PORTB, R20	; PORTB = R20
	
        RET
 
 ;; C-code
		/*R20 = PINA & 0x08;
		R20 = R20 >> 3;
		R21 = PORTB & 0xFE;
		R20 = R20 | R21;
		PORTB = R20;*/