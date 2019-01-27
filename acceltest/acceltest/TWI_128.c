#include "TWI_128.h"

void TWI_Init(void)
{
	TWSR = 0x00;							//No Pre_scaler
	TWBR = (((F_CPU/F_SCL) - 16) / 2);
}

void TWI_Start(void)
{
	TWCR = (1<<TWINT | 1<<TWEN | 1<<TWSTA);
	while(!(TWCR & (1<<TWINT)));
}

void TWI_Stop(void)
{
	TWCR = (1<<TWINT | 1<<TWEN | 1<<TWSTO);
}

void TWI_Send(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT | 1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	//if (!(((TWSR&0xF8) == TW_MT_SLA_ACK) || ((TWSR&0xF8) == TW_MR_SLA_ACK) || ((TWSR&0xF8) == TW_MT_DATA_ACK)))   //Check Status
	//{
		//TWI_Send(data);						  //Send data again
	//}
}

uint8_t TWI_ReadACK(void)
{
	TWCR = (1<<TWINT | 1<<TWEN | 1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
    return TWDR;
}

uint8_t TWI_ReadNACK(void)
{
	uint8_t Value;
	TWCR = (1<<TWINT | 1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	Value = TWDR;
	TWI_Stop();
	return Value;
	
}

void TWI_WriteRegister(uint8_t DeviceAdrr , uint8_t RegisterAdrr , uint8_t data)
{
	TWI_Start();
	TWI_Send(DeviceAdrr);
	TWI_Send(RegisterAdrr);
	TWI_Send(data);
	TWI_Stop();
}

uint8_t TWI_ReadRegisterACK(uint8_t DeviceAdrr , uint8_t RegisterAdrr)
{
	TWI_Start();
	TWI_Send(DeviceAdrr);
	TWI_Send(RegisterAdrr);
	TWI_Start();
	TWI_Send(DeviceAdrr + 1);
	return TWI_ReadACK();
}

uint8_t TWI_ReadRegisterNACK(uint8_t DeviceAdrr , uint8_t RegisterAdrr)
{
	
	TWI_Start();
	TWI_Send(DeviceAdrr);
	TWI_Send(RegisterAdrr);
	//TWI_Stop();
	TWI_Start();
	TWI_Send(DeviceAdrr + 1);
	return TWI_ReadNACK();
}