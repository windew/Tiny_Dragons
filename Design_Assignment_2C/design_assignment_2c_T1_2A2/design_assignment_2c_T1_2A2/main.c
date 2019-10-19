/*
 * design_assignment_2c_T1_2A2.c
 *
 * Created: 10/14/2019 1:09:19 AM
 * Author : Moriah
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	unsigned char count = 0;  //count to keep track of timer0
    DDRC &= 0b1000;            // connect PORTC.2 to switch as input
    PORTC |= 0b1000;     // enable pull-up on port c
    DDRB |= 0b0100;            // set PORTB.2 for output

	while (1) 
    {
		//set timer0 with prescalar 256 and normal mode
		TCCR0A = 0;
		TCCR0B |= (1<<CS02);
		
		TCNT0 = 0;		//counter initiallized
			while((TIFR0 & 0X1) == 0);  //WAIT for overflow
			
			TCCR0B = 0; //stop timer
			TIFR0 |= 1; //clear overflow
			
			
			if(!(PINC & (1<<PINC2))){  // check if pin is low
				PORTB &= ~0b0100;          // set LED on
				if (count < 200)   //edit
					{
						count++;
					
					}
				else{                                    // otherwise (pin is high)
					PORTB |= 0b0100;           // LED off
				else {
						count =0;
				}
				
				
				
				
				
    }
}
	
	}
}
