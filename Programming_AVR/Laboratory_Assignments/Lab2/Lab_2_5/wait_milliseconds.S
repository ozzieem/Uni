        .text
;;;===Subroutine wait_milliseconds========================
;;;   C-prototype:  void wait_milliseconds(int milliseconds);
;;;                 Parameter 1 is passed in registerpair R24:R25
        .global wait_milliseconds				
wait_milliseconds:
wait_milliseconds_loop:
        RCALL   wait1ms
        SBIW    R24,1           ;Subtract R25:R24=R25:R24-1
        BRNE    wait_milliseconds_loop
wait_milliseconds_end:

        RET

;;;===Subroutine wait1ms===================================
;;;   C-prototype:  void wait1ms(void);
        .global wait1ms				
wait1ms:

        RCALL    wait500microseconds
        RCALL    wait500microseconds
        RET
        

;;;===Subroutine wait250microseconds=======================
wait250microseconds:   ;; 16MHz clock <-> 1 machine cycle = 62.5 ns
wait500microseconds:   ;; 8MHz clock <-> 1 machine cycle = 125 ns
        LDI     R18, 210
        ;; Register R25-R18 can be used as scratch pad register
        ;; due to the GNU C calling conventions.
				
        
        
wait_loop:
        LD       R19,X
        LD       R19,X
        LD       R19,X
        LD       R19,X
        LD       R19,X
        LD       R19,X
        LD       R19,X
        LD       R19,X
        DEC     R18
        BRNE    wait_loop
        
        RET
				
