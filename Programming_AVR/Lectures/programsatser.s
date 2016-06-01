;; Villkorliga programsatser i assemblernivå
;;
;; C-kod:
;; if(counter > 10)
;; {
;; 		count = 0;
;; }
;; else
;; {
;;		counter++;
;; }
;;
;; Test <=> Ofta en subtraktion
;;			SUB ; Påverkar ett register, dvs resultat läggs i ett register
;;		
;;			SUB R20, R21	; R20 = R20 - R21
;;			CP R20, R21		; R20 - R21
;;
;; Assembler-kod

			.data
counter:	.word 0 ; int counter = 0

			.text
L00_TEST: 
			LDS R24, counter		; Load Direct From Dataspace - R24 = counter
			LDS R25, counter+1		; R25 = counter++
			SBIW R24, 11			; Subtract Immediate from Word
			BRLT L00_ELSE			; Branch If Less Than
			
L00_IF:
			STS counter, R1			; Store Direct to Dataspace 
			STS counter+1, R1		
			RJMP L00_END			; JMP to L00_END

L00_ELSE:
			LDS R24, counter		;
			LDS R25, counter+10
			ADDIW R24, 0x01			; R25:R24 = R25:R24+10
			SDS counter, R24		
			SDS counter+1, R25
			
L00_END:
			
			
			
			
			
