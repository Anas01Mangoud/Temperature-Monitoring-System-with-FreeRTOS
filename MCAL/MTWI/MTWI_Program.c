/*
 * MTWI_Program.c
 *
 *  Created on: Nov 30, 2021
 *      Author: gerges
 */

#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"
#include"MTWI_Private.h"
#include"MTWI_Config.h"
#include"MTWI_Interface.h"

/*TWI Initialization as a master with set Master Address*/
void MTWI_VidInitMaster(u8 Copy_u8Address)
{
	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,6);
	/*Set SCL Frequency To 400KHz,with 16Mhz system frequency*/
	/*1- Set TWBR=12*/
	TWBR=12;
	/*2- Clear The prescaler bits (TWPS)*/
	CLR_BIT(TWSR,1);
	CLR_BIT(TWSR,0);
	/*Check if master will be addressed*/
	if(Copy_u8Address!=0)
	{
		/*Set the required Address in the 7MSB Of TWAR*/
		TWAR=Copy_u8Address<<1;
	}
	else
	{
		/*Do Nothing*/
	}
	/*Enable TWI*/
	SET_BIT(TWCR,2);
}
/*TWI Initialization as a Slave with set Master Address*/
void MTWI_VidInitSlave(u8 Copy_u8Address)
{
	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,6);
	/*Set the required Address in the 7MSB Of TWAR*/
	TWAR=Copy_u8Address<<1;
	/*Enable TWI*/
	SET_BIT(TWCR,2);
}

TWI_ErrStatus MTWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_Error=NoError;

	/*Send Start Condition*/
	SET_BIT(TWCR,5);
	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
	/*Wait until the operation finished and the flag is raised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check Operation Status*/
	if((TWSR&0xF8)!=START_ACK)
	{
		Local_Error=StartConditionErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus MTWI_SendRepeatedStart(void)
{
	TWI_ErrStatus Local_Error=NoError;

	/*Send Start Condition*/
	SET_BIT(TWCR,5);
	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
	/*Wait until the operation finished and the flag is raised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check Operation Status*/
	if((TWSR&0xF8)!=REP_START_ACK)
	{
		Local_Error=RepeatedStartErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}

TWI_ErrStatus MTWI_SendSlaveAddresWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error=NoError;

	/*Send 7bits Slave Address To the bus*/
	TWDR=Copy_u8SlaveAddress<<1;
	/*Set the Write request in the LSB in the data Register*/
	CLR_BIT(TWDR,0);
	/*Clear Start Condition Bit*/
	CLR_BIT(TWCR,5);
	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
	/*Wait until the operation finished and the flag is raised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check Operation Status*/
	if((TWSR&0xF8)!=SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error=SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus MTWI_SendSlaveAddresWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error=NoError;

	/*Send 7bits Slave Address To the bus*/
	TWDR=Copy_u8SlaveAddress<<1;
	/*Set the Read request in the LSB in the data Register*/
	SET_BIT(TWDR,0);
	/*Clear Start Condition Bit*/
	CLR_BIT(TWCR,5);
	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
	/*Wait until the operation finished and the flag is raised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check Operation Status*/
	if((TWSR&0xF8)!=SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error=SlaveAddressWithReadErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}

TWI_ErrStatus MTWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_Error=NoError;

	/*Send 8bits data To the bus*/
	TWDR=Copy_u8DataByte;
	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
	/*Wait until the operation finished and the flag is raised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check Operation Status*/
	if((TWSR&0xF8)!=MSTR_WR_BYTE_ACK)
	{
		Local_Error=MasterWriteByteErr;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus MTWI_MasterReadDataByte(u8* Copy_pu8DataByte)
{
	TWI_ErrStatus Local_Error=NoError;

	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
	/*Wait until the operation finished and the flag is raised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check Operation Status*/
	if((TWSR&0xF8)!=MSTR_RD_BYTE_ACK)
	{
		Local_Error=MasterReadByteErr;
	}
	else
	{
		/*Read the received data*/
		*Copy_pu8DataByte=TWDR;
	}
	return Local_Error;
}

void MTWI_SendStopCondition(void)
{
	/*Sent stop condition on the bus*/
	SET_BIT(TWCR,4);
	/*Clear the interrupt flag To start the previous operation*/
	SET_BIT(TWCR,7);
}
