/*
 * MTWI_Interface.h
 *
 *  Created on: Nov 30, 2021
 *      Author: gerges
 */

#ifndef MCAL_MTWI_MTWI_INTERFACE_H_
#define MCAL_MTWI_MTWI_INTERFACE_H_

typedef enum
{
	NoError,
	StartConditionErr,
	RepeatedStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr
}TWI_ErrStatus;

/*TWI Initialization as a master with set Master Address*/
void MTWI_VidInitMaster(u8 Copy_u8Address);
/*TWI Initialization as a Slave with set Master Address*/
void MTWI_VidInitSlave(u8 Copy_u8Address);

TWI_ErrStatus MTWI_SendStartCondition(void);
TWI_ErrStatus MTWI_SendRepeatedStart(void);

TWI_ErrStatus MTWI_SendSlaveAddresWithWrite(u8 Copy_u8SlaveAddress);
TWI_ErrStatus MTWI_SendSlaveAddresWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrStatus MTWI_MasterWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrStatus MTWI_MasterReadDataByte(u8* Copy_pu8DataByte);

void MTWI_SendStopCondition(void);

#endif /* MCAL_MTWI_MTWI_INTERFACE_H_ */
