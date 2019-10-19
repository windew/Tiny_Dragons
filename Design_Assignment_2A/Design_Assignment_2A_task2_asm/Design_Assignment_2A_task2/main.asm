;
; Design_Assignment_2A_task2.asm
;
; Created: 9/30/2019 9:20:31 PM
; Author : Moriah Wingrove
;


; Replace with your application code

;Task Two 
;Connect a switch to portc.3(active high -turn on and pull up transistor) to poll for and event to turn on led at portb.2 for 1.33 sec after the event
.org 0 
	cbi DDRC, 3 ;sets port c as input
	sbi portc, 3 ; sets port c bit 2 high to enable pull up
	sbi ddrb, 2 ;sets port b as output
	cbi portb, 2  ;LED is off

poll_loop:
	sbic pinc, 3	;if pinc is low (0) skip next instruction
	jmp LED			;jumps to label led 
	sbi portb, 2	;turn on led


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



LED:
	cbi portb, 2	 ;turns led off
	jmp poll_loop	;go to label poll_loop
	