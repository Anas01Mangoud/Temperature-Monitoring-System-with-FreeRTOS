/*
 * MSPI_Interface.h
 *
 *  Created on: Nov 29, 2021
 *      Author: gerges
 */

#ifndef MCAL_MSPI_MSPI_INTERFACE_H_
#define MCAL_MSPI_MSPI_INTERFACE_H_

/*SPI Master Initialization*/
void MSPI_VidMaster_Init(void);
/*SPI Slave Initialization*/
void MSPI_VidSlave_Init(void);
/*SPI Send and Receive Char*/
u8 MSPI_u8Send_Receive_Char(u8 Copy_u8Char);

#endif /* MCAL_MSPI_MSPI_INTERFACE_H_ */
