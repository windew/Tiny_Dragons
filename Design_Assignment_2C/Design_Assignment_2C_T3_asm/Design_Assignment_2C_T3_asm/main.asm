;
; Design_Assignment_2C_T3_asm.asm
;
; Created: 10/13/2019 3:29:25 AM
; Author : Moriah Wingrove
;

.org 0x00 ;reset location
	jmp main
.org 0x1c	;location for timer0 cmpA
	jmp t0_cm_isr

main:
	ldi r23, 23 ;MAKE 23 FOR 375 DELAY
	ldi r24,0x3e
	cbi portb,3  ;led off	
timer:
	OUT	SPH,R20
	LDI	R20,LOW(RAMEND)
	OUT	SPL,R20
	LDI	R20,0xff		
	OUT	OCR0A,R20	;OCR0A
	LDI	R20,0x02	;(1<<WGM01)	
	OUT	OCR0B,R20	;Timer in CTC mode
; Force Output Compare A 
	LDI	R20,0x0d	 ; 
	OUT	TCCR0B,R20     ; Force Output & Start Timer0
	SBI	DDRB,3	     ;PB3 as an output
	LDI	R20,(1<<OCIE0A) ;Timer0 compare match 
	sts	TIMSK0, r20 
	SEI	;Set I – SET Main Interrupt Enable after all config

wait:	JMP	wait

;--------ISR for Timer 0	
t0_cm_isr:
	LDI R20, (1<<OCF0A)
	OUT	TIFR0, R20
	dec r23			;timer needs to overflow 
	brne timer
	sbi portb,3	
	timeron:
	ldi r21, (1<<tov0)
	out TIFR0, r21	;clear overflow
	ldi r20, 0x00	;r20 = 0
	out tcnt0, r20  ;load timer 0 
	ldi r21, (1<<CS02)  ; 
	out TCCR0B, r21;   send r21 out to timer
check:
	in r21, TIFR0	;read overflow
	sbrs r21, 0;   skip if overflow occurs 
	jmp check
	out tccr0b, r22 ; stop timer
	ldi r21, (1<<tov0)
	out TIFR0, r21	;clear overflow
	dec r24
	brne timeron
	rjmp main