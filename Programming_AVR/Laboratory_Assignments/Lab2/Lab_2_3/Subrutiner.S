
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

#define oldValue R22
#define newValue R23

counter: .byte 0

;;;--- subrutin init_func ---
	.text
	.global init_func
         
init_func:

	LDI R20, 0xFF
	OUT DDRB, R20

	LDI R21, 0x00
	OUT DDRA, R21
		
	RET

	.text
	.global loop_func

loop_func:

	MOV oldValue, newValue
	/*IN R19, PINA
	ANDI R19, 0x01*/
	EOR R19, oldValue	;För automatisk räkning utan intryckning
	MOV newValue, R19
	
	CP oldValue, newValue
	BRNE loop_if
	RJMP loop_end

loop_if:
	
	LDS R18, counter
	INC R18
	STS counter, R18
	RJMP loop_end

loop_end:
	
	COM R18
	OUT PORTB, R18
	CLR R18

	RET


	
		
