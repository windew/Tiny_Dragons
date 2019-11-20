/*
 * Design_Assignment_4B_task2.c
 *
 * Created: 11/13/2019 9:46:51 AM
 * Author : Moriah Wingrove
 */ 

//Task two: Write an AVR C program to control the position of the Servo Motor using a potentiometer 
//			connected to PC0. When pot value is 0 the servo is at position
//			0 deg. and when pot value is max (approx. 5V) the servo is at position 180 deg 



#define F_CPU 16000000UL								/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>									/* Include AVR std. library file */
#include <util/delay.h>								/* Include Delay header file */



void main()
{
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).

	DDRB|=(1<<PB1);   //PWM Pins as Out

	while(1)
	{

		OCR1A=97;   //0 degree
		_delay_ms(200);

		OCR1A=316;  //90 degree
		_delay_ms(200);

		OCR1A=425;  //135 degree

		_delay_ms(200);

		OCR1A=535;  //180 degree
		_delay_ms(200);
	}
}