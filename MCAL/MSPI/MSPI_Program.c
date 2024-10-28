/*
 * MSPI_Program.c
 *
 *  Created on: Nov 29, 2021
 *      Author: gerges
 */

#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"
#include"MSPI_Private.h"
#include"MSPI_Config.h"
/*SPI Master Initialization*/
void MSPI_VidMaster_Init(void)
{
	/*Set Data Ordered*/
#if MSPI_SET_DATA_ORDERED==MSPI_DATA_ORDERED_LSB
	SET_BIT(SPCR,5);
#elif MSPI_SET_DATA_ORDERED==MSPI_DATA_ORDERED_MSB
	CLR_BIT(SPCR,5);
#else
#error"SPI Data Ordered option is not valid..."
#endif
	/*Set Clock Polarity*/
#if MSPI_SET_CLOCK_POLARITY==MSPI_CPOL_LEADING_RISING
	CLR_BIT(SPCR,3);
#elif MSPI_SET_CLOCK_POLARITY==MSPI_CPOL_LEADING_FALLING
	SET_BIT(SPCR,3);
#else
#error"SPI Data Clock Polarity option is not valid..."
#endif
	/*Set Clock Phase*/
#if MSPI_SET_CLOCK_PHASE==MSPI_CPHA_LEADING_SAMPLE
	CLR_BIT(SPCR,2);
#elif MSPI_SET_CLOCK_PHASE==MSPI_CPHA_LEADING_SETUP
	SET_BIT(SPCR,2);
#else
#error"SPI Data Clock Phase option is not valid..."
#endif
	/*Set Double SPI Speed Bit*/
#if MSPI_SET_DOUBLE_SPEED==MSPI_NO_DOUBLE_SPEED
	CLR_BIT(SPSR,0);
#elif MSPI_SET_DOUBLE_SPEED==MSPI_DOUBLE_SPEED
	SET_BIT(SPSR,0);
#else
#error"SPI Data Clock Phase option is not valid..."
#endif
	/*Set SPI Interrupt Enable*/
#if MSPI_SET_SPI_INTERRUPT_ENABLE ==MSPI_SPI_INTERRUPT_ENABLE
	SET_BIT(SPCR,7);
#elif MSPI_SET_SPI_INTERRUPT_ENABLE ==MSPI_SPI_INTERRUPT_DISABLE
	CLR_BIT(SPCR,7);
#else
#error"SPI Interrupt Enable option is not valid..."
#endif
	/*set SPI Clock Rate Select*/
	SPCR&=MSPI_BIT_MASKING;
	SPCR|=MSPI_SET_CLOCK_RATE;
	/*Set Master Mode*/
	SET_BIT(SPCR,4);
	/*SPI Enable*/
	SET_BIT(SPCR,6);
}
/*SPI Slave Initialization*/
void MSPI_VidSlave_Init(void)
{
	/*Set Data Ordered*/
#if MSPI_SET_DATA_ORDERED==MSPI_DATA_ORDERED_LSB
	SET_BIT(SPCR,5);
#elif MSPI_SET_DATA_ORDERED==MSPI_DATA_ORDERED_MSB
	CLR_BIT(SPCR,5);
#else
#error"SPI Data Ordered option is not valid..."
#endif
	/*Set Clock Polarity*/
#if MSPI_SET_CLOCK_POLARITY==MSPI_CPOL_LEADING_RISING
	CLR_BIT(SPCR,3);
#elif MSPI_SET_CLOCK_POLARITY==MSPI_CPOL_LEADING_FALLING
	SET_BIT(SPCR,3);
#else
#error"SPI Data Clock Polarity option is not valid..."
#endif
	/*Set Clock Phase*/
#if MSPI_SET_CLOCK_PHASE==MSPI_CPHA_LEADING_SAMPLE
	CLR_BIT(SPCR,2);
#elif MSPI_SET_CLOCK_PHASE==MSPI_CPHA_LEADING_SETUP
	SET_BIT(SPCR,2);
#else
#error"SPI Data Clock Phase option is not valid..."
#endif
	/*Set SPI Interrupt Enable*/
#if MSPI_SET_SPI_INTERRUPT_ENABLE ==MSPI_SPI_INTERRUPT_ENABLE
	SET_BIT(SPCR,7);
#elif MSPI_SET_SPI_INTERRUPT_ENABLE ==MSPI_SPI_INTERRUPT_DISABLE
	CLR_BIT(SPCR,7);
#else
#error"SPI Interrupt Enable option is not valid..."
#endif

	/*Set Slave Mode*/
	CLR_BIT(SPCR,4);
	/*SPI Enable*/
	SET_BIT(SPCR,6);
}
/*SPI Send and Receive Char*/
u8 MSPI_u8Send_Receive_Char(u8 Copy_u8Char)
{
	/*Send Char*/
	SPDR=Copy_u8Char;
	/*wait on SPI Interrupt Flag is set to one*/
	while(GET_BIT(SPSR,7)==0);
	return SPDR;
}
