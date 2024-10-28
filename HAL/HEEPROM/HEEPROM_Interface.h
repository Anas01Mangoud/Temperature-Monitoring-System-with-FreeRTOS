/*
 * HEEPROM_Interface.h
 *
 *  Created on: Nov 30, 2021
 *      Author: gerges
 */

#ifndef HAL_HEEPROM_HEEPROM_INTERFACE_H_
#define HAL_HEEPROM_HEEPROM_INTERFACE_H_

/*Send byte to EEPROM*/
void HEEPROM_VidSendDataByte(u8 Copy_u8LocationAddress,u8 Copy_u8ChipNum,u8 Copy_u8BlockNum,u8 Copy_u8DataByte);
/*Read byte to EEPROM*/
u8 HEEPROM_VidReadDataByte(u8 Copy_u8LocationAddress,u8 Copy_u8ChipNum,u8 Copy_u8BlockNum);


#endif /* HAL_HEEPROM_HEEPROM_INTERFACE_H_ */
