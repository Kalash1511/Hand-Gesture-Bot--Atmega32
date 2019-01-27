/*
 * adc.c
 *
 * Created: 2/4/2018 6:33:31 PM
 * Author : hp
 */ 
#define  F_CPU 8000000UL
#define  F_ADC 50000
#include <avr/io.h>
#include "USART_128.h"



void adc_init()
{
	//configure adc
	//ADMUX |=(1<<ADLAR);//LEFT 
	ADMUX |=(1<<REFS0);//AVCC IS SET FOR REFERENCE
	ADCSRA |=(1<<ADPS2);//enable THE PRESCALER OF 16
	ADCSRA |=(1<<ADEN);//turn on adc
	//ADCSRA |=( 1<<ADFR);//START CONVERSION  With free running mode 
}

uint8_t adc_read()
{
	//ADCSRA |= (1<<ADSC);//start conversion
	 // wait for conversion to complete
	 // ADSC becomes 0 again
	 // till then, run loop continuously
	 while(ADCSRA & (1<<ADSC));
	 
	 return (ADCH);//using 8 BIT RESOLUTION 
}

uint16_t adc_readnew(uint8_t ch)
{
	// select the corresponding channel 0~7
	// ANDing with ’7? will always keep the value
	// of ‘ch’ between 0 and 7
	ch &= 0X07;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}
int main(void)
{
	USART_Init(51,0);
    // Replace with your application code 
	adc_init();
	
    while (1) 
    {
		USART_Transmitchar('a',0);
		_delay_ms(50);
		//int value=adc_readnew(0X00);
 		USART_TransmitNumber(10,1);
		
    }
}

