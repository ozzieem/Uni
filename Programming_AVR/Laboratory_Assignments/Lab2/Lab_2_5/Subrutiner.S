
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

varX: .byte 0
varY: .byte 0

	.text
	.global init_func
         
init_func:

	LDI R20, 0xFF
	OUT DDRB, R20
	RET

	.text
	.global loop_func

loop_func:
	
	CALL seven
	CALL seven
	CALL seven
	CALL thirty
	RET

seven:

	LDS R21, varX
	INC R21
	STS varX, R21

	; varX = 7 ? reset : seven
	CPI R21, 0x08
	BREQ reset
	CALL display
	RJMP seven

thirty:

	LDS R21, varY
	DEC R21
	DEC R21
	STS varY, R21

	; varY = 0 ? reset : thirty
	CPI R21, 0x00
	BREQ reset
	CALL display
	RJMP thirty

reset:

	LDI R21, 0x00
	STS varX, R21
	LDI R21, 0x1E
	STS varY, R21
	CLR R21
	RET

display:

	; wait_milliseconds ~0.25s
	LDI R24, 0
	LDI R25, 1
	CALL wait_milliseconds

	; display to PORTB
	COM R21
	OUT PORTB, R21
	COM R21
	RET
	
	
	