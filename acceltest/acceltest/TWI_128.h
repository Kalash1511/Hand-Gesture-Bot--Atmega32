#ifndef TWI_128
#define	TWI_128

#define F_CPU		8000000UL
#define F_SCL		100000UL
#include <avr/io.h>
#include <util/twi.h>


void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Send(uint8_t data);
void TWI_WriteRegister(uint8_t DeviceAdrr , uint8_t RegisterAdrr , uint8_t data);

uint8_t TWI_ReadACK(void);
uint8_t TWI_ReadNACK(void);
uint8_t TWI_ReadRegisterACK(uint8_t DeviceAdrr , uint8_t RegisterAdrr);
uint8_t TWI_ReadRegisterNACK(uint8_t DeviceAdrr , uint8_t RegisterAdrr);

#endif