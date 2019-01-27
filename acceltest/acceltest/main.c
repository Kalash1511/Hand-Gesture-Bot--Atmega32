/*
 * acceltest.c
 *
 * Created: 09-02-2018 22:06:26
 * Author : admin
 */ 

# define F_CPU 8000000UL
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include "TWI_128.h" 
#include "USART_128.h"
uint8_t Data;
int ACCEL_XOUT;
int ACCEL_YOUT;
int ACCEL_ZOUT;


float ACCEL_XOFFSET;
float ACCEL_YOFFSET;
float ACCEL_ZOFFSET;

int8_t ACCEL_XOUT_L;
int8_t ACCEL_XOUT_H;
int8_t ACCEL_YOUT_L;
int8_t ACCEL_YOUT_H;
int8_t ACCEL_ZOUT_L;
int8_t ACCEL_ZOUT_H;

float Get_Accel_X()
{
	ACCEL_XOUT = TWI_ReadRegisterNACK(0x68<<1,0x3B);
	ACCEL_XOUT = ACCEL_XOUT<<8;
	ACCEL_XOUT |= TWI_ReadRegisterNACK(0x68<<1,0x3C);
	float a= ((float)ACCEL_XOUT/16384)-ACCEL_XOFFSET;
	return a;
}

float Get_Accel_Y()
{
	
	ACCEL_YOUT = TWI_ReadRegisterNACK(0x68<<1,0x3D);
	ACCEL_YOUT = ACCEL_YOUT<<8;
	ACCEL_YOUT |= TWI_ReadRegisterNACK(0x68<<1,0x3E);
	float a=((float)ACCEL_YOUT/16384)-ACCEL_YOFFSET;
	return a;
	
}

float Get_Accel_Z()
{
	ACCEL_ZOUT = TWI_ReadRegisterNACK(0x68<<1,0x3F);
	ACCEL_ZOUT = ACCEL_YOUT<<8;
	ACCEL_ZOUT |= TWI_ReadRegisterNACK(0x68<<1,0x40);
	float a = ((float)ACCEL_ZOUT/16384)-ACCEL_ZOFFSET;
	return a;
}

void Acceleration_config()											//Removing initial zero error, device should be kept horizontal initially
{
	
	float ACCEL_XOFFSETSUM=0,ACCEL_YOFFSETSUM=0, ACCEL_ZOFFSETSUM=0;
	for(int i =0;i<500;i++)
	{
		ACCEL_XOFFSETSUM +=Get_Accel_X();
		ACCEL_YOFFSETSUM +=Get_Accel_Y();
		ACCEL_ZOFFSETSUM += Get_Accel_Z();
	}
	
	ACCEL_ZOFFSET=ACCEL_ZOFFSETSUM/500.0;
	ACCEL_XOFFSET=ACCEL_XOFFSETSUM/500.0;
	ACCEL_YOFFSET=ACCEL_YOFFSETSUM/500.0;
}

int main(void)
{
	USART_Init(51,0);
	TWI_Init();
	Acceleration_config();
   // sei();
	TWI_WriteRegister(0x68<<1,0x6B,0x00);
	
    while (1) 
    {
	//	USART_Transmitchar('k',0);
		//USART_Transmitchar('h',0);
		
// 		Data = TWI_ReadRegisterNACK(0x68<<1,0x3C);
// 		USART_Transmitchar(Data, 0);
 		//USART_Transmitchar('h',0);
 /*		USART_Transmitchar('X',0);
 		USART_TransmitFloat(Get_Accel_X(),0);
 		USART_Transmitchar('y',0);
 		USART_TransmitFloat(Get_Accel_Y(),0);
 		USART_Transmitchar('z',0);
 		USART_TransmitFloat(Get_Accel_Z(),0);
		USART_Transmitchar(0x0D,0);*/
		
		float x=Get_Accel_X();
		float y=Get_Accel_Y();
		float z=Get_Accel_Z();
		float pitch = -(atan(x/sqrt((y*y)+(z*z))))*(180/3.1415);
		//float roll = (atan(y/z)*180/3.1415); 
		float roll= -(atan(y/sqrt((x*x)+(z*z))))*(180/3.1415);
//  		USART_Transmitchar('p',0);
//  		USART_TransmitFloat(pitch,0);
 // 		USART_Transmitchar('r',0);
//  		USART_TransmitFloat(roll,0);
		USART_Transmitchar(0x0D,0);
/*		
		while(1)
		{
			if((pitch>=-20 && pitch<=20) && (roll>=-20 && roll<=20))
		{
		 USART_Transmitchar('s',0); 					
		}
		else
		{
		while(pitch>0)
		{
			while(roll>0)
			{
				if(pitch>roll)
				{
					USART_Transmitchar('f',0);
				}
				else
				{
					USART_Transmitchar('r',0);
				}
			}
			while(roll<0)
			{
				if(pitch>(-roll))
				{
					USART_Transmitchar('f',0);
				}
				else
				{
					USART_Transmitchar('l',0);
				}
			}
		}
			while(pitch<0)
			{
				while(roll>0)
				{
					if((-pitch)>roll)
					{
						USART_Transmitchar('b',0);
					}
					else
					{
						USART_Transmitchar('r',0);
					}
				}
				while(roll<0)
				{
					if((-pitch)>(-roll))
					{
						USART_Transmitchar('b',0);
					}
					else
					{
						USART_Transmitchar('l',0);
					}
				}
			}
		}
		}*/
		if((pitch>-20 && pitch<20) && (roll>-20 && roll<20))
		{
			USART_Transmitchar('s',0);
		}
		else
		{

		if(pitch>0 && roll>0)
		{
			if(pitch>roll)
			{
				USART_Transmitchar('b',0);
			}
			else
			{
				USART_Transmitchar('l',0);
			}
		}
		else if(pitch<0 && roll<0)
		{
			if(pitch>roll)
			{
				USART_Transmitchar('r',0);
			}
			else
			{
				USART_Transmitchar('f',0);
			}
		}
		else if(pitch>0 && roll<0)
		{
			if(pitch>(-roll))
			{
				USART_Transmitchar('b',0);
			}
			else
			{
				USART_Transmitchar('r',0);
			}
		}
		else
		{
			if((-pitch)>roll)
			{
				USART_Transmitchar('f',0);
			}
			else
			{
				USART_Transmitchar('l',0);
			}
		}
		}



	
		_delay_ms(200);
    }
}

