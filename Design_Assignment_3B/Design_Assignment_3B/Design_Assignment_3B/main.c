/*
 * Design_Assignment_3B.c
 *
 * Created: 10/16/2019 12:05:36 PM
 * Author : Moriah Wingrove
 */ 


//TASK ONE: Write a C AVR program that will monitor the LM34/35 connected to an Analog pin (PC5) to display
//			the temperature in F on the serial terminal every 1 sec. Use a timer with interrupt delay for the 
//			1 sec delay. Use a FTDI chip for serial to USB conversion.
//TASK TWO: Use the ATMEL Studio Data Visualizer or any charting program to display the values 

 
#define F_CPU 16000000UL //16 Mhz. 
#define BAUDRATE 9600 //Set Baud rate 9600. 
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>
void read_adc(void); // Function Declarations 
void adc_init(void);
void USART_init(void);
unsigned char USART_receive(void); 
void USART_transmit(unsigned char data); //function to send through USART
void USART_tx_string( char *data ); 
volatile unsigned int adc_temp; 

char outs[20];


uint8_t OVF_COUNT = 0; //initialize the overflow count for interrupt
uint8_t OVF_LIMIT = 250; //set the limit the count can reach to set 1 sec delay


int main(void) { 
	 adc_init(); // Initialize the ADC (Analog / Digital Converter)  
	USART_init(); // Initialize the USART (RS232 interface) 
	USART_tx_string("Connected!\r\n"); // we're alive!  
	_delay_ms(125); // wait a bit  
	while(1)  
	{  
		read_adc();   // snprintf(outs,sizeof(outs),
		//"%3d\r\n", adc_temp);
		// print it   
		USART_tx_string(outs);   
		_delay_ms(1000); // wait a bit  
	} 
} 
void adc_init(void)
{  
	/** Setup and enable ADC **/  
	ADMUX = (0<<REFS1)| // Reference Selection Bits  
	(1<<REFS0)| // AVcc - external cap at AREF  
	(0<<ADLAR)| // ADC Left Adjust Result  
	(1<<MUX2)| // ANalog Channel Selection Bits  
	(0<<MUX1)| // ADC2 (PC2 PIN25)  
	(0<<MUX0);  
	ADCSRA = (1<<ADEN)| // ADC ENable  
	(0<<ADSC)| // ADC Start Conversion  
	(0<<ADATE)| // ADC Auto Trigger Enable  
	(0<<ADIF)| // ADC Interrupt Flag  
	(0<<ADIE)| // ADC Interrupt Enable  
	(1<<ADPS2)| // ADC Prescaler Select Bits
	(0<<ADPS1)|  
	(1<<ADPS0);  // Timer/Counter1 Interrupt Mask Register  
	TIMSK1 |= (1<<TOIE1); // enable overflow interrupt  
	TCCR1B |= (1<<CS11)|(1<<CS10);  // native clock  
	TCNT1 = 49911; 
} 
/* READ ADC PINS */ 
void read_adc(void) 
{  
	unsigned char i =4;  
	adc_temp = 0;  
	while (i--) {   
					ADCSRA |= (1<<ADSC);   
					while(ADCSRA & (1<<ADSC));   
					adc_temp+= ADC;  
					_delay_ms(50);  
			    }  
	adc_temp = adc_temp /3; // Average a few samples  
	//int tempf= (adc_temp*5*100);  
	snprintf(outs,sizeof(outs),"%3d\r\n", adc_temp);// print it  
	USART_tx_string(outs); 
}

void USART_init(void) 
{  
	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
} 
/* SEND A STRING TO THE RS-232 */


unsigned char USART_receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void USART_transmit(unsigned char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}


void USART_tx_string(char* data)
{
	while(*data != 0x00)
	{
		USART_transmit(*data);
		data++;
	}
}

ISR(TIMER1_OVF_vect)
{
	OVF_COUNT++; //increment the overflow counter
	if (OVF_COUNT == OVF_LIMIT) //check to see if the limit was reached
	{
		ADCSRA|=(1<<ADSC);	//start conversion
		while((ADCSRA&(1<<ADIF))==0);//wait for conversion to finish
		
		ADCSRA |= (1<<ADIF);

		int a = ADCL;
		a = a | (ADCH<<8);
		a = (a/1024.0) * 5000/10;
		a = (a*2)+32; //equation to convert celsius to farenheit. can't use used 2 instead of 9/5
		a = a % 100;
		USART_transmit((a/10)+'0');
		a = a % 10;
		USART_transmit((a)+'0');
		USART_transmit('\n');
		OVF_COUNT = 0; //reset overflow counter
	}
	TCNT0 = 16; //reset TOP
}


