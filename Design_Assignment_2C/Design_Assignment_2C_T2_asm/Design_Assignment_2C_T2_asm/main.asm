;
; Design_Assignment_2C_T2_asm.asm
;
; Created: 10/13/2019 1:37:35 AM
; Author : Moriah
;


;TASK 2: Implement design assignment 2A using Timer0_OVF_vect interrupt mechanism in normal mode.
		 ;2A was to generate a waveform on portb.3 with 40% DC and 0.625s period

.org 0				;location of main prgm
	jmp main		;go to main prgm
.org 0x20			;location on interrupt
	jmp T0_OVF		;jmp to interrupt

main:
	sbi ddrb,3		;pb3 is an output 
	cbi portb, 3	;Led is off
	ldi r23, 0x58



timer:
	ldi r20, 0x0	;r20 = 0
	out tcnt0, r20  ;load timer 0 
	ldi r22, 0x00
	out tccr0a, r22	; timer0, normal
	ldi r21, (1<<CS02) |(1<<CS00)  ; 
	out TCCR0B, r21;   send r21 out to timer

	;enable interrupts
	ldi r20, 0x01	;r20 =1
	sts TIMSK0, r20; store r20 in TIMSKO - enables interrupt overflow
	sei          ; interrupts enabled
wait:
	jmp wait   ;loop until interrupt occurs
T0_OVF:
	out tccr0b, r22 ; stop timer
	ldi r21, (1<<tov0)
	out TIFR0, r21	;clear overflow
	dec r23			;timer needs to overflow 
	brne done

	sbi portb, 3	;turn on led
	ldi r23, 0x3e

timeron:
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
	dec r23
	brne timeron
	rjmp main
done:
	ldi r20, 0x00	;r20 = 0
	out tcnt0, r20  ;load timer 0 
	ldi r21, (1<<CS02)  ; 
	out TCCR0B, r21;   send r21 out to timer

	reti