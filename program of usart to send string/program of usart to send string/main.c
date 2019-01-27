/*
 * program of usart to send string.c
 *
 * Created: 2/6/2018 7:32:47 PM
 * Author : hp
 */ 

/*
 * usart sending string.c
 *
 * Created: 2/4/2018 11:57:02 AM
 * Author : hp
 */ 

#define F_CPU 8000000UL
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
void uart_transmit_string(char* strptr)
{
	
	while (*strptr !='\0')
	{
		uart_transmit(*strptr);
		strptr++;
	
	}
}



int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		char string []="kalash";
		uart_transmit_string(string);
		_delay_ms(10);
    }
}




