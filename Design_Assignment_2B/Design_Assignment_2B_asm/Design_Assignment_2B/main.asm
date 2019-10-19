;
; Design_Assignment_2B.asm
;
; Created: 10/5/2019 10:02:00 AM
; Author : Moriah Wingrove
;


; TASK ONE: Implement design assignment 2A.2 using INTO (PD2 pin) interrupt mechanism
;			2A.2: connect switch to PORTC.3(active high - turn on to pull up transistor) to poll for even to turn on
;			      LED at PORTB.2 for 1.333 seconds after event 





.include <m328pbdef.inc>	;include file for atmega328PB
	
.org 0x00	;location for reset 
jmp main	;begin main program 
.org 0X02	;location of interupt PD2 
jmp EXO_ISR	;external interrupt program

main:
	ldi r20, high(RAMEND)		;initialize stack
	out sph, r20				;initialize stack
	ldi r20, low(RAMEND)		;initialize stack
	out spl, r20				;initialize stack

	

	
	ldi r20, 0x2	;make INTO falling edge triggered
	sts EICRA, r20
	
	sbi portd, 2	;pull up activated
	
	cbi DDRC, 3		;sets port c as input for switch
	sbi portc, 3	; sets port c bit 2 low switch not connected
	sbi ddrb, 2		;sets port b as output
	cbi portb, 2	;LED is off


	ldi r20, 1<<INT0 ;enable INT0
	out EIMSK, r20
	SEI			;enable interrupts 
;wait:	
	;  		jmp wait	;wait for interrupt

EXO_ISR:
	in r21, portc
	sbic pinc, 3	;if pinc is low (0) skip next instruction
	jmp LED			;jumps to label led 
	sbi portb, 2	;turn on led
	out portc, r21

; 1s 333ms at 16 MHz
    ldi  r18, 109		;r18 = 109
    ldi  r19, 51		;r19 = 51
    ldi  r20, 106		;r20 = 106
L1: dec  r20			;decrement r20
    brne L1				;if r20 != 0 go to label l1
    dec  r19			;decrement r19
    brne L1				;if r20 != 0 go to label l1
    dec  r18			;decrement r19
    brne L1				;if r18 != 0 go to label l1

LED:	cbi portb, 2	 ;turns led off
	RETI


