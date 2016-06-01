
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

;;;--- Variables ---
        .data
togglePINA: .byte 0
pflancPINA: .byte 0
nflancPINA: .byte 0
oldPINA:    .byte 0xFF
		      
;;;--- subrutin init_func ---
        .text
        .global init_func
         
init_func:

        LDI		R20, 0x00
		OUT		DDRA,R20

		LDI		R20, 0xFF
		OUT		DDRB,R20

		LDI		R20,0b11111111
		OUT		PORTB,R20
        RET

;;;--- subrutin loop_func ---
        .text
        .global loop_func

loop_func:
		CALL	pina_func

		LDS		R21 , togglePINA
		OUT		PORTB, R21
        RET

;;;=========================================
pina_func:
		LDS		R21 , oldPINA
        IN		R20 , PINA		;R20=PINA
		STS		oldPINA , R20
		COM		R20				;R20=~PINA
		AND		R20 , R21       ;R20=~PINA & oldPINA
		STS     nflancPINA, R20

		LDS		R21 , togglePINA
		EOR		R21, R20		
		STS		togglePINA,R21
		RET


 
