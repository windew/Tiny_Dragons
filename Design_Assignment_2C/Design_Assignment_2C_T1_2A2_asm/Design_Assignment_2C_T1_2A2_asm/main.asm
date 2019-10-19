;
; Design_Assignment_2C_T1_2A2_asm.asm
;
; Created: 10/14/2019 12:14:14 AM
; Author : Moriah Wingrove
;

;TASK 1: Implement design assignment 2A using Timer 0 - normal mode. Count OVF occurrence if needed. Do not use interrupts
		 ;2A Connect a switch to PORTC.3 (active high - turn on the pull up transistor) 
		 ;to poll for an event to turn on the led at PORTB.2 for 1.333 sec after the event.  

begin:
	cbi DDRC, 3 ;sets port c as input
	sbi portc, 3 ; sets port c bit 2 high to enable pull up
	sbi ddrb, 2 ;sets port b as output
	cbi portb, 2  ;LED is off

	poll_loop:
	sbic pinc, 3	;if pinc is low (0) skip next instruction
	jmp LED			;jumps to label led 
	sbi portb, 2	;turn on led

	ldi r23, 0x5b 
	ldi r24, 0x02 
timer:
	ldi r20, 0x0f	;r20 = 0
	out tcnt0, r20  ;load timer 0 
	ldi r22, 0x00
	out tccr0a, r22	; timer0, normal
	ldi r21, (1<<CS02)  ; 
	out TCCR0B, r21;   send r21 out to timer
check:
	in r21, TIFR0	;read overflow
	sbrs r21, 0;   skip if overflow occurs 
	jmp check
	out tccr0b, r22 ; stop timer
	ldi r21, (1<<tov0)
	out TIFR0, r21	;clear overflow
	dec r23
	brne timer
	dec r24
	brne timer

LED:
	cbi portb, 2	 ;turns led off
	jmp poll_loop	;go to label poll_loop


