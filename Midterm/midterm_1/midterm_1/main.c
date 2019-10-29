


#define F_CPU 16000000UL //16 Mhz.
#define BAUDRATE 115200 //Set Baud rate 9600.
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 8UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

void read_adc(void); // Function Declarations
void adc_init(void); //function that initializes ADC
void USART_init(void); //initializes USART
unsigned char USART_receive(void); //fn that receives USART
void USART_transmit(unsigned char data); //function to send through USART
void USART_tx_string( char *data );
volatile unsigned int adc_temp;

char outs[20];


uint8_t OVF_COUNT = 0; //initialize the overflow count for interrupt
uint8_t OVF_LIMIT = 250; //set the limit the count can reach to set 1 sec delay


int main(void) {
	adc_init(); // Initialize the ADC (Analog / Digital Converter)
	USART_init(); // Initialize the USART (RS232 interface)
	
	USART_tx_string("AT\r\n"); // 
	_delay_ms(500); // wait a bit
	USART_tx_string("AT+CWMODE=3\r\n");
	_delay_ms(500); // wait a bit
	
	USART_tx_string("AT+CWJAP=\"WIFI_NAME_HERE\",\"WIFI_PASSWORD_HERE\""); // // Log in WiFi	
	_delay_ms(500);
	
	USART_tx_string("AT+CIPMUX=0\r\n");
	_delay_ms(500);
	

/////////////////////////////////////////////////
	//TCCR0A = 0x00; //normal operation
	//TCCR0B |= (1 << CS00); //set prescalar to 256
	//TCNT0 = 1; //TOP = 256-240 = 16
	//TIMSK0 |= (1 << TOIE0);
	//sei(); //enable interrupt
////////////////////////////////////////////////////////	
	//while(1)
	//{
		//keep waiting
	//}
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
}
/* READ ADC PINS */



void USART_init(void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0A = (1 << U2X0);   // double mode for more accuracy
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}


/* SEND A STRING TO THE RS-232 */


unsigned char USART_receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void USART_transmit(unsigned char data) {			// Function to transmit ASCII value into UDR0
	while (!(UCSR0A & (1 << UDRE0)));			// Keep Checking until  UDRE0 data register 'High' to break loop
	UDR0 = data;								// Store unsigned char serial data into UDR0
}


void USART_tx_string(char* data)
{
	while(*data != 0x00)
	{
		USART_transmit(*data);
		data++;
	}
//}

//ISR(TIMER1_OVF_vect)
//{
	//OVF_COUNT++; //increment the overflow counter
	//if (OVF_COUNT == OVF_LIMIT) //check to see if the limit was reached
	//{
		ADCSRA|=(1<<ADSC);	//start conversion
		while((ADCSRA&(1<<ADIF))==0);//wait for conversion to finish
		
		ADCSRA |= (1<<ADIF);

		int a = ADCL;
		a = a | (ADCH<<8);
		a = (a/1024.0) * 5000/10;
		a = (a*2)+32; //equation to convert celsius to farenheit. can't use used 2 instead of 9/5
			
		
		
		USART_tx_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");	// Connect API KEy
		_delay_ms(500);
		USART_tx_string("AT+CIPSEND=51\r\n");	
		_delay_ms(500);
		USART_tx_string("GET /update?key=QTJ31HQI0KR0Q5AP&field1=");// Send Value
		_delay_ms(500);
		a = a % 100;
		USART_transmit((a/10)+'0');
		a = a % 10;
		USART_transmit((a)+'0');
		_delay_ms(500);
		USART_transmit('\n');
		_delay_ms(500);
		
		OVF_COUNT = 0; //reset overflow counter
	
	TCNT0 = 16; //reset TOP
}

