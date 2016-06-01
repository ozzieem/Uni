;; Subrutiner.s för flankdetektering			
;;
;; _______            _____________	-PINA
;;	  ^   |__________|   ^
;;   old   ^ 		^	new
;;	  	  new	   old  
;;		   _
;; _______| |______________________	-negative flanc	
;;		   ^
;;		  puls vid negativ flank varar T sekunder
;;						 _					
;; _____________________| |_________	-positive flanc
;;						 ^
;;		  puls vid positiv flank varar T sekunder
;;	
;;
;;		nf = old * ~new
;;		pf = ~old * new
;;
;;	toggle+ = toggle XOR nf
;;

			.data
togglePINA:	.byte 0 	;unsigned char togglePINA = 0
pflancPINA:	.byte 0		;positiv flank
nflancPINA:	.byte 0		;negativ flank
oldPINA:	.byte 0xFF	;föregående PIN


			.text
			.global init_func
init_func:
			LDI R20, 0x00
			OUT	DDRA, R20 
			LDI	R20, 0xFF
			OUT DDRB, R20
			OUT PORTB, R20	; Släck alla dioder
			
			RET
			
			;; (IN och OUT arbetar med IO-adress. 
			;;  6 bitar => 2^6 adresser)
			
			
			.text
			.global loop_func
loop_func:
			CALL pina_func
			LDS R21, togglePINA
			OUT PORTB, R21
			
			RET
			
			
pina_func:
			LDS R21, oldPINA		; Dataminnesadress 16 bitar
			IN R20, PINA			; R20 = new PINA
			STS oldPINA, R20		; oldPINA = PINA
			COM R20					; R20 = ~PINA
			AND R20, R21			; R20 = ~PINA & oldPINA
			STS nflancPINA, R20 	; nflancPINA = ~PINA & oldPINA
			LDS R21, togglePINA		; R21 = new togglePINA 
			EOR R21, R20
			STS togglePINA, R21
			
			RET
			

			
			