
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

;;;; CHECK INSTRUCTION MANUAL FOR SPECIFIC INSTRUCTIONS

;;;--- Variables ---
        .data
		.global LEDS

LEDS: .byte 0x00, 0x81, 0xC3, 0xE7, 0xFF, 0xE7, 0xC3, 0x81

        .text
        .global init_func
         
init_func:
		;; i = 0
		LDI R28, 0x00
		LDI R29, 0x00

		;; DDRB = 0xFF
		LDI	R24, 0xFF
		OUT DDRB, R24

        RET

        .text
        .global loop_func

loop_func:
		
		;; PORTB = LEDS[i]
		LDI R30, lo8(LEDS)
		LDI R31, hi8(LEDS)
		
		;; LEDS + i - R31:R30 + R29:R28
		ADD R30, R28
		ADC	R31, R29

		LD	R24, Z		;; Z = R31:R30
		/* COM R24 */
		OUT	PORTB, R24

		ADIW R28, 0x01	;; i += 1
		 
		;; i = i & 0x07
		ANDI R28, 0x07
		ANDI R29, 0x00

		RET
