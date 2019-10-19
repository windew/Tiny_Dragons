/*
 * DA2A_C.c
 *

 * Author : Moriah Wingrove
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    DDRB |= 0b1000;        // set PORTB.3 for output   
    while (1) 
    {
              _delay_ms(250);       // delay for 250ms
PORTB |= 0b1000;    // set LED on
              _delay_ms(375);      // delay for remaining 375ms
PORTB &= ~0b1000;    // set LED off
    }
}

 

