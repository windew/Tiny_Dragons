/*
 * DA2B_T2.c
 *
 
 * Author : Moriah Wingrove
 */ 
#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
 int main(void)
{
       DDRC &= 0b1000;            // connect PORTC.2 to switch as input
       PORTC |= 0b1000;     // enable pull-up on port c 
       DDRB |= 0b0100;            // set PORTB.2 for output
       while(1){
              if(!(PINC & (1<<PINC2))){  // check if pin is low
                     PORTB &= ~0b0100;          // set LED on
                     _delay_ms(1333);           // delay of 1.33 sec
              }
              else{                                    // otherwise (pin is high)
                     PORTB |= 0b0100;           // LED off
              }
       }
       return 0;
}

    }

