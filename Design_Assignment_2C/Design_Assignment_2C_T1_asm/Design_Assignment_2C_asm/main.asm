;
; Design_Assignment_2C_asm.asm
;
; Created: 10/10/2019 9:56:13 PM
; Author : Moriah Wingrove
;


; Goal: Use GPIO and delays using timers and interupts:

;TASK 1: Implement design assignment 2A using Timer 0 - normal mode. Count OVF occurrence if needed. Do not use interrupts
		 ;2A was to generate a waveform on portb.3 with 40% DC and 0.625s period

begin:
	sbi ddrb,3		;pb3 is an output 
	cbi portb, 3	;Led is off
	ldi r23, 0x61
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


blink:
	ldi r23,0x41
   sbi portb, 3          ; turn on LED on Portb bit 3
timer2:
	ldi r20, 0x0f	;r20 = 0
	out tcnt0, r20  ;load timer 0 
	ldi r22, 0x00
	out tccr0a, r22	; timer0, normal
	ldi r21, (1<<CS02)  ; 
	out TCCR0B, r21;   send r21 out to timer
check2:
	in r21, TIFR0	;read overflow
	sbrs r21, 0;   skip if overflow occurs 
	jmp check2
	out tccr0b, r22 ; stop timer
	ldi r21, (1<<tov0)
	out TIFR0, r21	;clear overflow
	dec r23
	brne timer2

   rjmp begin            ; loop back to the start

	
