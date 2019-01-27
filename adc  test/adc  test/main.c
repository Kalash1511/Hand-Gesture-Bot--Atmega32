/*
 * usart send character.c
 *
 * Created: 2/3/2018 9:09:31 PM
 * Author : hp
 */ 
//defining macros
#define F_CPU 8000000UL
#define F_ADC 125000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUDRATE 9600 //SET baud
#define ubrr ((F_CPU)/(BAUDRATE*16UL)-1) //setting the value of baud rate ASYNCHRONOUS normal mode U2X=0

//INITIALISATION FUNCTION
void uart_init(void)
{
	UBRR1H=(ubrr>>8);//FOR USING BAUDRATE GREATER THAN 8 BIT
	UBRR1L=ubrr;
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1);//RECEIVE AND TRANSMITTING ENABLED
	UCSR1C|=(1<<UCSZ10)|(1<<UCSZ11);//8 BIT DATA SEND
	UCSR1C|=(1<<UPM11);//PARITY BIT SET EVEN PARITY BIT MODE
	//ASYNCHRONOUS MODE WITH STOP BIT 1
}

//transmitting character
void uart_transmit(unsigned char data)
{
	while(!(UCSR1A & (1<<UDRE1)));//UDRE1 PIN IS SET high IMPLYING UDR1 IS READY TO RECIEVE DATA
	
	UDR1=data;
	
}


//recieving character
unsigned char uart_recieve(void)
{
	while(!( UCSR1A & (1<<RXC1)));//RXC1 PIN IS SET high  DATA IS RECIEVED
	
	return UDR1 ;//UDR SAVE DATA
	
	
}

void adc_init()
{
	//configure adc
	ADMUX |=(1<<ADLAR);//LEFT
	ADMUX |=(1<<REFS0);//AVCC IS SET FOR REFERENCE
	ADCSRA |=(1<<ADPS2)|(1<<ADPS1);//enable THE PRESCALER OF 64
	ADCSRA |=(1<<ADEN);//turn on adc
	//ADCSRA |=( 1<<ADFR);//START CONVERSION  With free running mode
}

uint16_t adc_read()
{
	//ADCSRA |= (1<<ADSC);//start conversion
	// wait for conversion to complete
	// ADSC becomes 0 again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	uint8_t thelow =ADCL;
	uint16_t tenbitvalue=ADCH<<8|thelow;
	
	return (tenbitvalue);//using 10 BIT RESOLUTION
}
 //transmitting character
 void uart_transmit(unsigned char data)
 {
	 while(!(UCSR1A & (1<<UDRE1)));//UDRE1 PIN IS SET high IMPLYING UDR1 IS READY TO RECIEVE DATA
	 
	 UDR1=data;
	 
 }
 
 
 void USART_TransmitNumber( uint16_t num)
 {
	 if(num<0)
	 {
		 uart_transmit('-');
		 num=(-1)*num;
	 }
	 
	 if(num >= 10)
	 {
		 USART_TransmitNumber(num/10);
		 num = num%10;
	 }
	 uart_transmit(num+'0'); /* n is between 0 and 9 */
	 
 }


// main function
int main(void)
{
	
	uart_init();
	adc_init();
	while (1)
	{
		 uint16_t r=adc_read();
		 USART_TransmitNumber(r);
		
	}
}

