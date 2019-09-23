;
; Assignment1A.asm
;
; Assignment1A.asm
;
; Created: 9/19/2019 1:19:00 PM
; Author : Moriah Wingrove
;


; Replace with your application code
start:
    LDI R24,LOW(0x2b2b)       ;Load low bits of 2b2b multiplicand into R24, R24 = 2b
    LDI R25,HIGH(0x2b2b)	  ;Load high bits of multiplicand into R25, R25 = 2b
    LDI R22,LOW(0xffcb)       ;Load low bits of multiplier into R22, R22 = cb
    LDI R23,HIGH(0xffcb)	  ;Load high bits of multiplier into R23, R23 = ff
		
	   
		LDI R16, 16          ;R16 is used as a bit counter
LOOP:   LSR R23               ;Shift Multiplier to the right
        ROR R22               ;Shift lowest bit into Carry Flag
        BRCC SKIP           ;If carry is zero skip addition 
        ADD R19,R24          ;Add low bit of Multiplicand into R19
        ADC R20,R25          ;Add high bit of multiplicand into answer of R20
SKIP:   ROR R20             ;Rotate high bits of result into lower
        ROR R19             ; Rotate high bits of result into lower
        ROR R18             ; Rotate high bits of result into lower
        ROR R17             ; Rotate high bits of result into lower
        DEC R16                ;Decrease counter
        BRNE LOOP           ;if counter does not equal zero loop  
end: jmp end 

