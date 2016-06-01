#define	VJOHN R20
#define ONE R21
#define VJOHN_AND R22

VJOHN_TEMP: .byte 0

        .text
        .global init_func
         
init_func:

		LDI		VJOHN, 0xFF
		OUT		DDRB, VJOHN			;; Initierar lysdioderna f�r anv�ndning 

		LDI		VJOHN, VJOHN_TEMP	;; R20 = vjohn <=> R20 = 0
		LDI		ONE, 1				;; R21 = 1

        RET

        .text
        .global loop_func

loop_func:

		LDS		VJOHN, VJOHN_TEMP	;; R20 = vjohn
		MOV		VJOHN_AND, VJOHN	;; R22 = R20
		ANDI	VJOHN_AND, 0x80		;; R22 & 0x80	(s� att v�rdet i VJOHN inte �ndras)
		BREQ	IF_EQUAL
		RJMP	ELSE

IF_EQUAL:
	
		LSL		VJOHN			;; R20 << 1
		ADD		VJOHN, ONE		;; R20 += R21
		RJMP	END_LOOP_FUNC

ELSE:

		LSL		VJOHN			;; R20 << 1
		RJMP	END_LOOP_FUNC

END_LOOP_FUNC:
		
		STS VJOHN_TEMP, VJOHN

		COM		VJOHN				;; Inverterar f�r lysdioderna
		OUT		PORTB, VJOHN
		
		RET
		