/*
 * MTWI_Interface.h
 *
 *  Created on: Nov 30, 2021
 *      Author: gerges
 */

#ifndef MCAL_MTWI_MTWI_PRIVATE_H_
#define MCAL_MTWI_MTWI_PRIVATE_H_

#define TWBR     *((volatile u8*)0x20)
#define TWCR     *((volatile u8*)0x56)
#define TWSR     *((volatile u8*)0x21)
#define TWDR     *((volatile u8*)0x23)
#define TWAR     *((volatile u8*)0x22)

#define START_ACK      0x08
#define REP_START_ACK  0x10
#define SLAVE_ADD_AND_WR_ACK  0x18
#define SLAVE_ADD_AND_RD_ACK  0x40
#define MSTR_WR_BYTE_ACK      0x28
#define MSTR_RD_BYTE_ACK      0x50

#endif /* MCAL_MTWI_MTWI_INTERFACE_H_ */
