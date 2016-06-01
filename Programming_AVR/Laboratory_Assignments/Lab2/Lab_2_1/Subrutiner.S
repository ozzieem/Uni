
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

#define vjohn R20
#define vjohn_and R21
#define vring R22

vjohn_temp: .byte 0

;;;--- subrutin init_func ---
	.text
	.global init_func
         
init_func:

 	LDI	R18, 0xFF
	OUT	DDRB, R18
	
	LDI	R17, 0x00
	OUT	DDRA, R17

	LDI	vjohn, vjohn_temp

    RET

;;;--- subrutin loop_func ---
	.text
	.global loop_func

loop_func:
		
	IN vjohn, PINA
	MOV R19, vjohn
	ANDI R19, 0x01
	BREQ ring_f
	RJMP john_f

ring_f:

	LSL vring		;vring
	CPI vring, 0x00
	BREQ ring_eq
	RJMP ring_end

ring_eq: 

	LDI vring, 0x01
	RJMP ring_end
	
ring_end:
	
	COM vring
	OUT PORTB, vring
	COM vring
	RET

john_f:

	LDS	vjohn, vjohn_temp
	MOV	vjohn_and, vjohn
	ANDI vjohn_and, 0x80
	BREQ john_if
	RJMP john_else

john_if:

	LSL vjohn
	INC vjohn
	RJMP john_end

john_else:

	LSL vjohn
	RJMP john_end

john_end:
	
	STS vjohn_temp, vjohn

	COM vjohn
	OUT PORTB, vjohn
	
	RET