
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

;;___________________________________________________________

/*
;; UPPGIFT A

;;;--- Variables ---
	.data

#define tCounter R18
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
	;IN R19, PINA
	;ANDI R19, 0x01
	EOR R19, oldValue	;För automatisk räkning utan intryckning
	MOV newValue, R19
	
	CP oldValue, newValue
	BRNE loop_if
	RJMP loop_end

loop_if:
	
	LDS tCounter, counter
	INC tCounter
	STS counter, tCounter
	CPI tCounter, 0x08
	BREQ reset_f
	RJMP loop_end

reset_f:

	LDI tCounter, 0x00
	STS counter, tCounter
	RJMP loop_end

loop_end:
	
	COM tCounter
	OUT PORTB, tCounter
	CLR tCounter

	RET
*/

;;______________________________________________________________

;; UPPGIFT B


;;;--- Variables ---
	.data

#define tCounter R18
#define oldValue R21
#define newValue R22

counter: .byte 0

;;;--- subrutin init_func ---
	.text
	.global init_func
         
init_func:

	LDI R20, 0xFF
	OUT DDRB, R20
	RET

count:

	MOV oldValue, newValue
	EOR R19, oldValue
	MOV newValue, R19
	RET

seven:

	CALL count
	LDS tCounter, counter
	INC tCounter
	STS counter, tCounter

	CPI tCounter, 0x08
	BREQ reset_f
	RJMP seven_end

thirty:
	
	CALL count
	LDS tCounter, counter
	DEC tCounter
	DEC tCounter
	STS counter, tCounter
	
	;; counter = 30 ? reset : end
	CPI tCounter, 0x1E	
	BREQ reset_f
	RJMP thirty_end

reset_f:

	LDI tCounter, 0x00
	LDI newValue, 0x00
	LDI oldValue, 0x00
	STS counter, tCounter
	COM tCounter
	OUT PORTB, tCounter
	CLR tCounter
	RET

seven_end:

	COM tCounter
	OUT PORTB, tCounter
	CLR tCounter
	LDI		R24, 0
	LDI		R25, 1
	CALL	wait_milliseconds
	RJMP seven

thirty_end:

	COM tCounter
	OUT PORTB, tCounter
	COM tCounter
	LDI	R24, 0
	LDI	R25, 1
	CALL wait_milliseconds
	RJMP thirty

	.text
	.global loop_func

loop_func:	

	CALL seven
	CALL seven
	CALL seven
	CALL thirty

	RET



	
		

	
		
