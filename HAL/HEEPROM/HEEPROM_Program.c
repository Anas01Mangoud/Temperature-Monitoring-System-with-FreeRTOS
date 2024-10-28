/*
 * HEEPROM_Program.c
 *
 *  Created on: Nov 30, 2021
 *      Author: gerges
 */

#define F_CPU 16000000UL
#include"..\..\LIB\LSTD_TYPES.h"

#include"..\..\MCAL\MTWI\MTWI_Interface.h"

#include"HEEPROM_Private.h"

#include<util\delay.h>


/*Send byte to EEPROM*/
void HEEPROM_VidSendDataByte(u8 Copy_u8LocationAddress,u8 Copy_u8ChipNum,u8 Copy_u8BlockNum,u8 Copy_u8DataByte)
{
	u8 Local_u8AddressPacket;
	Local_u8AddressPacket=EEPROM_FIXED_ADDRESS|(Copy_u8ChipNum<<2);
	Local_u8AddressPacket=Local_u8AddressPacket|Copy_u8BlockNum;
	/*Start Condition*/
	MTWI_SendStartCondition();
	/*Send Address Packet--> Address Of Chip and block*/
	MTWI_SendSlaveAddresWithWrite(Local_u8AddressPacket);
	/*Send the rest 8bit of location address*/
	MTWI_MasterWriteDataByte(Copy_u8LocationAddress);
	/*Send the data byte to memory location */
	MTWI_MasterWriteDataByte(Copy_u8DataByte);
	/*Send Stop condition*/
	MTWI_SendStopCondition();
	/*Delay until the write cycle is finished*/
	_delay_ms(10);

}
/*Read byte to EEPROM*/
u8 HEEPROM_VidReadDataByte(u8 Copy_u8LocationAddress,u8 Copy_u8ChipNum,u8 Copy_u8BlockNum)
{
	u8 Local_u8AddressPacket;
	u8 Local_u8DataByte;
	Local_u8AddressPacket=EEPROM_FIXED_ADDRESS|(Copy_u8ChipNum<<2);
	Local_u8AddressPacket=Local_u8AddressPacket|Copy_u8BlockNum;
	/*Start Condition*/
	MTWI_SendStartCondition();
	/*Send Address Packet--> Address Of Chip and block*/
	MTWI_SendSlaveAddresWithWrite(Local_u8AddressPacket);
	/*Send the rest 8bit of location address*/
	MTWI_MasterWriteDataByte(Copy_u8LocationAddress);
	/*Send Repeated Start*/
	MTWI_SendRepeatedStart();
	/*Send Address Packet With Read--> Address Of Chip and block*/
	MTWI_SendSlaveAddresWithRead(Local_u8AddressPacket);
	/*Get the data from memory*/
	MTWI_MasterReadDataByte(&Local_u8DataByte);
	/*Send Stop condition*/
	MTWI_SendStopCondition();

	return Local_u8DataByte;
}
