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
;;;--- 		SREG			   ---
#define SREG	0x3F 

        .data
		
#define valueX R20
#define valueY R21
        
        .text
        .global init_func
		
init_func:

		LDI R23, 0xFF
		OUT DDRB, R23

		LDI R23, 0x00
		OUT DDRA, R23

		LDI R23, 0x00
		OUT DDRD, R23
        
        RET

        .text
        .global loop_func

loop_func:

		IN R22, PINA
		COM  R22
		ANDI R22, 0xF0
		MOV valueX, R22

		IN R22, PINA
		COM R22
		LSL R22
		LSL R22
		LSL R22
		LSL R22
		MOV valueY, R22
		
		IN R23, PIND
		ANDI  R23, 0x01
		CPI R23, 0x01
		BRNE Subtract_func
		RJMP Add_func

Subtract_func:

		SUB valueX, valueY
		IN	R22, SREG
		COM valueX
		OUT PORTB, valueX
		RET

Add_func:

		ADD valueX, valueY
		ANDI valueX , 0xF0
		IN	R22, SREG
		ANDI R22, 0x0F
		OR valueX,R22
		COM valueX
		OUT PORTB, valueX
        RET
