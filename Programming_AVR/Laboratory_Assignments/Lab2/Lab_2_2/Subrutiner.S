
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

pattern: 
	.byte 0x10, 0x82, 0x92, 0xC6, 0xD6, 0xEE

;;;--- subrutin init_func ---
	.text
	.global init_func
         
init_func:

	LDI R20, 0xFF
	OUT DDRB, R20

	LDI R21, 0x00
	OUT DDRA, R21

	CLR R20
		
	RET

;;;--- subrutin loop_func ---
	.text
	.global loop_func

loop_func:

	IN R21, PINA
	ANDI R21, 0x01
	BREQ dice_update
	RJMP dice_end

dice_update:
		
	INC R20	; counter++
	CPI R20, 0x06
	BREQ dice_if
	RJMP dice_end

dice_if:

	LDI R20, 0x00
	RJMP dice_end

dice_end:
	
	LDI R30, lo8(pattern)
	LDI R31, hi8(pattern)

	ADD R30, R20
	LD R24, Z

	COM R24
	OUT PORTB, R24

	RET
		
