
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


;;; Två varianter på STOPPURsprogrammet
;;; Variant 1: START=sw0
;;;            STOPP=sw1
;;; Variant 2: START/STOPP=sw0
;;;            RESET=nollställ tid=sw7
;;;--- Variables ---
        .data
		.global	oldSw7
oldSw7:		.byte	1 ;STOPP 
oldSw0:		.byte	1 ;START
flagCount:	.byte	0
counter:	.word	0


;;===VARIANT 1 ====
		.text
		.global	sw7run

sw7run:
		;; R20 new sw7 value
		;; R21 old sw7 value
		LDI		R20,0
		SBIC	PINA,7	;OBS 7
		LDI		R20,1
			
		LDS		R21,oldSw7
		STS		oldSw7,R20

		LDI		R22,0b00000001 ;Negative flanc
		EOR		R20,R22

		AND		R20,R21
		BREQ	sw7runEnd				;Hopp om Z=1

		;; flagCount=0;
		CLR		R20
		STS		flagCount, R20
sw7runEnd:				
		RET

		.global	sw7run

sw0run:
		;; R20 new sw0 value
		;; R21 old sw0 value
		LDI		R20,0
		SBIC	PINA,0		;OBS 0
		LDI		R20,1
			
		LDS		R21,oldSw0
		STS		oldSw0,R20

		LDI		R22,0b00000001 ;Negative flanc
		EOR		R20,R22

		AND		R20,R21
		BREQ	sw0runEnd				;Hopp om Z=1

		;; flagCount=1;
		LDI		R20,1
		STS		flagCount, R20

		;; counter= 0;
		CLR		R20
		STS		counter,R20
		STS		counter+1,R20

sw0runEnd:				
		RET

;;;===VARIANT 2===
		.text
		.global resetRun
resetRun: //Positve flanc
		LDS			R21,oldSw7	
		IN			R20,PINA
		ANDI		R20,0b10000000	;SW7
		STS			oldSw7,R20

		LDI			R22, 0b10000000
		EOR			R21,R22

		AND			R20,R21

		BREQ		resetRunEnd

		CLR		R20
		STS			counter,R20
		STS			counter+1,R20

resetRunEnd:
		RET


		.global	startStopRun

startStopRun: //Negative flanc

		;; if ( oldSw0 && !newSw0 )
		;; {
		;;     flagCount = !flagCount
		;; }
		;; else ;
		;;
		;; oldSw0 = newSw0; //För nästa varv
		;;
		;; R20 new sw0 value
		;; R21 old sw0 value

startStopRun_IfTest:
		LDI		R20,0
		SBIC	PINA,0		;OBS 0
		LDI		R20,1
			
		LDS		R21,oldSw0
		STS		oldSw0,R20

		LDI		R22,0b00000001 ;Negative flanc
		EOR		R20,R22

		AND		R20,R21
		BREQ	startStopRun_IfElse				;Hopp om Z=1
startStopRun_If:
		;; flagCount=!flagCount;
		LDS		R20,flagCount
		LDI		R21,1
		EOR		R20,R21
		STS		flagCount, R20
		; RJMP	startStopRun_IfEnd
startStopRun_IfElse:
startStopRun_IfEnd:
		RET



;;;===Räkning gemensamt för variant 1 och 2
counterRun:
		LDS		R20,flagCount
		CPI		R20,0
		BREQ	counterRun_end
		LDI		R20, 0b00100000
		CLR		R21
		LDS		R24,counter
		LDS		R25,counter+1
		ADD		R24,R20
		ADC		R25,R21
		STS		counter,R24
		STS		counter+1,R25
counterRun_end:
		RET

		
        
;;;--- subrutin init_func ---
        .text
        .global init_func
         
init_func:
		;;DDRB=0xFF;
		LDI		R20,0xFF
		OUT		DDRB,R20
        RET

;;;--- subrutin loop_func ---
        .text
        .global loop_func

loop_func:
		;CALL	sw0run		;Variant 1
		;CALL	sw7run		;Variant 2

		CALL	resetRun	;Variant 2
		CALL	startStopRun;Variant 2
		CALL	counterRun

loop_func_end:
		LDS		R25,counter+1
		COM		R25
		OUT		PORTB,R25

        RET


