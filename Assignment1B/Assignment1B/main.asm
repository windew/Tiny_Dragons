;
; Assignment1B.asm
;
; Created: 9/21/2019 1:03:54 PM
; Author : Moriah Wingrove
;


; Replace with your application code
;

TASKONE:	
	.equ STARTADDS = 0X200	;beginning address
	LDI XL, LOW(STARTADDS)	;xl[7:0] =0x00
	LDI XH, HIGH(STARTADDS)	;xh[15:8]=0x02
	ldi yl, low(0x0300)		;yl[7:0] = 0x00
	ldi yh, high(0x0300)		;yh[15:0] = 0x03
	ldi zl, low(0x0500)		;zl[7:0] = 0x00
	ldi zh, high(0x0500)		;zh[15:8] = 0x05
	.equ counter = 251 		;counter of 250 numbers
	ldi r20, counter		;R20 = counter = 250
	ldi r22, 5			;r22 = 5  used to check div
	clr r2				;r2 = 0
start:	
	LDI R21, 3		;r21 = 3
	mov r1, XL 		; R1 = XL  
	add r1, XH 		; R1 = XL + XH 
	add r1, r21 		; R1 = XL + XH +3
	mov r3, r1		;store r1 value in r3 so it doesnt erase
	st X+, r3		;[X] = XL + XH +3
	

DIVBYFIVE:
	cp	r1, r22	;compare r1 to 5 if r1<5
	brlo NODIV		; go to NODIV
	sub r1, r22		;else r1 = r1 - r20 = R1-5
	cp	r1, r2		;compare r1 to 0 if r1 = 0
	breq DIV		;go to DIV
 	rjmp DIVBYFIVE	; go to DIVBYFIVE

DIV:
 	st Y+, r3	; [y] = XL + XH + 3
	add r16, r3	; R16 = R16 + R3 
	adc r17, r2	; R17 = R17 + R2 + C 
	rjmp done	; go to DONE

NODIV:
	st Z+, r3	; [Z] = XL + XH + 3
	add r18, r3	; R18 = R18 + R3 
	adc r19, r2	; R19 = R19 + R2 + C 
	rjmp done	; go to DONE

done: 
		dec r20		;decrement counter
		brne start		;if all 250 numbers not added to memory back to start

end : rjmp end


