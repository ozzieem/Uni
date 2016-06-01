
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

// UTAN IF-ELSE JOHNSONRÄKNARE

/*
;;;--- Variables ---
        .data

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
		COM		R21			;; Kommentera bort för en ringräknare
		ROL		R21	
		ROL		R20

		OUT PORTB, R20

		RET

*/

// IF-ELSE FÖR JOHNSON

;; Naming registers
#define	vjohn R20
#define one R21
#define vjohn_and R22

vjohn_temp: .byte 0

        .text
        .global init_func
         
init_func:

		LDI		vjohn, 0xFF
		OUT		DDRB, vjohn			;; Initierar lysdioderna för användning 

		LDI		vjohn, vjohn_temp	;; R20 = vjohn <=> R20 = 0
		LDI		one, 1				;; R21 = 1

        RET

        .text
        .global loop_func

loop_func:

		LDS		vjohn, vjohn_temp	;; R20 = vjohn
		MOV		vjohn_and, vjohn	;; R22 = R20
		ANDI	vjohn_and, 0x80		;; R22 & 0x80	(så att värdet i vjohn inte ändras)
		BREQ	if_equal
		RJMP	else

if_equal:
	
		LSL		vjohn			;; R20 << 1
		ADD		vjohn, one		;; R20 += R21
		RJMP	end_loop_func

else:

		LSL		vjohn			;; R20 << 1
		RJMP	end_loop_func

end_loop_func:
		
		STS		vjohn_temp, vjohn

		COM		vjohn				;; Inverterar för lysdioderna
		OUT		PORTB, vjohn
		
		RET
		
