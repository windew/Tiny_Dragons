/*
 * Design_Assignment_4A.c
 *
 * Created: 10/29/2019 7:55:13 PM
 * Author : Moriah Wingrove
 */ 

//Task One: Write an AVR C program to control the speed of the DC Motor using a potentiometer connected to PC0. 
//			Use an interrupt on a button (PC1/2/3) to stop and start the motor at each click. The minimum speed 
//			of the motor should be 0 when pot is at minimum position and at maximum position should be 95%
//			of PWM value


#define F_CPU 8000000UL // clock is 8MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_adc(void);
int control; // controlling the motor with potentiometer
int toggle = 0; // to toggle the motor with the switch

int main()
{
	DDRC = 0xFB; // set Port C as outputs, leave INT1(PC3) as interrupt
	PORTC = 0x00; // pull-up pins

	EIMSK = 0x02; // enable INT1
	EIFR = 0x02; // enable interrupt flag
	EICRA = 0X0C; // set interrupt on rising edge

	sei(); // enable interrupts
	init_adc(); // initiate adc 
	TCCR0A=0x83; // set fast PWM // clear OCR0A on MATCH
	TCCR0B=0x03; // set prescaler to 1024
	
	while (1)
	{
		while((ADCSRA&(1<<ADIF))==0); // wait for conversion
		control = ADC*80/100; // ADC Conversion
		OCR0A = control; // Output to converted value to 0CR0A
		
		if(toggle == 0) // when switch is NOT pressed
		{
			PORTC = 0x00; //
		}
	}
}
void init_adc(void) // Initiate ADC function
{
	ADMUX = (1<<REFS0); // Reference voltage at Aref
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// from ADCRSA we Enable ADC, Start Conversion, Set prescalar as 128
}

ISR(INT1_vect)
{
	toggle ^= 1; // toggle switch on INT1 Interrupt
}