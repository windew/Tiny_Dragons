/*
 * Design_Assignment_2B_C.c
 *
 * Created: 10/6/2019 12:00:49 AM
 * Author : Moriah
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRC &= 0b1000;            // connect PORTC.2 to switch as input
	PORTC |= 0b1000;     // enable pull-up on port c
	DDRB |= 0b0100;            // set PORTB.2 for output
	PORTD = 1<<2;		// pull up activated
	EICRA = 0x2;	//make INT0 falling edge 
	
	EIMSK = (1<<INT0);	//enable external interrupt 0
	sei (); //enable interrupts
	
	while(1); //wait here for interrupt
	}
	
ISR (INT0_vect)	//isr for external interrup 0
	if(!(PINC & (1<<PINC2))){  // check if pin is low
		PORTB &= ~0b0100;          // set LED on
		_delay_ms(1333);           // delay of 1.33 sec
	}
	else{                                    // otherwise (pin is high)
		PORTB |= 0b0100;           // LED off
return


