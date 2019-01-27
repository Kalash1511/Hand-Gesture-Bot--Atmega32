/*
 * BOT CODE.c
 *
 * Created: 2/14/2018 5:21:54 PM
 * Author : hp
 */ 
//defining macros
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "USART_128.h"
#define BAUDRATE 9600 //SET baud
#define ubrr ((F_CPU)/(BAUDRATE*16UL)-1) //setting the value of baud rate ASYNCHRONOUS normal mode U2X=0
/*
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
*/
void forward(void)
{
	PORTC=0b01010101;
	/*PORTC=PORTC|(1<<PINC0)|(1<<PINC2)|(1<<PINC4)|(1<<PINC6);//m1 m2 m3 m4 forwardS
	PORTC=PORTC&(~(1<<PINC1));
	PORTC=PORTC&(~(1<<PINC3));
	PORTC=PORTC&(~(1<<PINC5));
	PORTC=PORTC&(~(1<<PINC7));*/
}
void backward(void)
{
	PORTC=0b10101010;
	/*PORTC=PORTC|(1<<PINC1)|(1<<PINC3)|(1<<PINC5)|(1<<PINC7);//m1 m2 m3 m4 backward
	
	PORTC=PORTC&(~(1<<PINC0));
	PORTC=PORTC&(~(1<<PINC2));
	PORTC=PORTC&(~(1<<PINC4));
	PORTC=PORTC&(~(1<<PINC6));*/
	
}
void left (void)
{
	PORTC=0b00010001;
	/*PORTC=PORTC|(1<<PINC0)|(1<<PINC2)|(1<<PINC4)|(1<<PINC6);//m1 forward m2 stop m3 forward m4 stop
	PORTC=PORTC&(~(1<<PINC1));
	PORTC=PORTC|(1<<PINC3);
	PORTC=PORTC&(~(1<<PINC5));
	PORTC=PORTC|(1<<PINC7);*/
	
}
void right (void)
{
	PORTC=0b01000100;
		/*PORTC=PORTC|(1<<PINC0)|(1<<PINC2)|(1<<PINC4)|(1<<PINC6);//m1 stop m2 forwad m3 stop m4 forward
		PORTC=PORTC|(1<<PINC1);
		PORTC=PORTC&(~(1<<PINC3));
		PORTC=PORTC|(1<<PINC5);
		PORTC=PORTC&(~(1<<PINC7));*/
}
void stop()
{
	PORTC=0X00;
		/*PORTC=PORTC|(1<<PINC0)|(1<<PINC2)|(1<<PINC4)|(1<<PINC6)|(1<<PINC1)|(1<<PINC3)|(1<<PINC5)|(1<<PINC7);//all stop*/
}
int main(void)
{
    /* Replace with your application code */
	
	DDRC=0b00000000;
	PORTC=0b00000000;
	USART_Init(51,1);
	//uart_init();
    while (1) 
    {
		char x='0',y='0',z='0';
		x=USART_Receive(1);
		USART_Transmitchar(x,1);
		if(x=='f'&&y=='f'&&z=='f')
			forward();
		else if(x=='b'&&y=='b'&&z=='b')
			backward();
		else if(x=='l'&&y=='l'&&z=='l')
			left();
		else if(x=='r'&&y=='r'&&z=='r')
			right();
		else if(x=='s'&&y=='s'&&z=='s')
			stop();
		else 
			right();
		z=y;
		y=x;
	}
		
			
    
}

