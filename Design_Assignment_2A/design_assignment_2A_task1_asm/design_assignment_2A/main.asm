;
; design_assignment_2A.asm
;
; Created: 9/27/2019 2:14:43 PM
; Author :Moriah Wingrove


; Replace with your application code

.include<m328pbdef.inc>

;Task One 
;Design delay subroutine to generate waveform on portb.3 with 40% duty cycle and 0.625 sec per period 

	
	sbi DDRB, 3           ; set Port b to output

blink:
   sbi portb, 3          ; turn on LED on Portb bit 3
   rcall delay_250ms     ; delay will be 250ms
   cbi portb, 3          ; turn off LED on  portb bit 3 
   rcall delay_375ms      ; delay will be 375 ms
   rjmp blink            ; loop back to the start

; Delay 4 000 000 cycles
; 250ms at 16 MHz
delay_250ms:
    ldi  r18, 21	;r18 = 21
    ldi  r19, 75	;r19 = 75
    ldi  r20, 191	;r20 = 191
L1: dec  r20	;decremenet r20
    brne L1		;if r20 != 0 go again
    dec  r19	;decrement r19
    brne L1		;if r19 != 0 go again
    dec  r18	;decrement r18
    brne L1		;if r18 != 0 go again
    nop			
	ret

; Delay 6 000 000 cycles
; 375ms at 16 MHz
delay_375ms:
    ldi  r18, 31	;r18 = 31
    ldi  r19, 113	;r19 = 113
    ldi  r20, 31	;r20 = 31
L2: dec  r20		;decremenet r20
    brne L2		;if r20 != 0 go again
    dec  r19		;decrement r19
    brne L2			;if r19 != 0 go again
    dec  r18		;decrement r18
    brne L2		;if r18 != 0 go again
    nop
	ret




