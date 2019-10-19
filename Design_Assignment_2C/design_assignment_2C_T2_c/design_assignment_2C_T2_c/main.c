/*
 * design_assignment_2C_T2_c.c
 *
 * Created: 10/13/2019 1:48:29 PM
 * Author : Moriah Wingrove
 */ 
#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/io.h>
#include <avr/interrupt.h> 
// 1Mhz clock & 64 prescaler
 // global variable for keeping track of # of times Timer0 overflows
volatile int count;

// this interrupt service routine (ISR) runs whenever an overflow on Timer0 occurs
 
 
 int main(void) {
	 
	 count = 0;  // initialize count to keep track of number of
	 DDRB |= (1 << 3);   // connect LED to pin PB.2
	 PORTB = 0; //led is off
	 // set up Timer0 with prescaler = 1024 and normal mode
	 TCCR0A = 0;
	 TCCR0B |= (1 << CS02)|(1 << CS00);
	 TCNT0 = 0;    // initialize counter
	 TIMSK0 |= (1 << TOIE0);  // enable overflow interrupt
	 sei();     // enable global interrupts
	 
 while(1) ;    // loop forever 
 }

 
 
 
 
 ISR (TIMER0_OVF_vect)
 {
	 if (count > 21)
	 {
		 PORTB |= (1 << 3);   // Toggle PB.3
		 if(count < 37 )
			{
				count++;
			}
		else
			{
				count = 0;
				PORTB = 0;
				count++;  // reinitialize count
			}    
	 }
	 else  count++;
 }
 
 
 
 