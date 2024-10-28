/*
 * main.c
 *
 *  Created on: Jan 10, 2022
 *      Author: Infotech
 */

#include "LIB/LSTD_TYPES.h"

#include "HAL/HCLCD/HCLCD_Interface.h"
#include "MCAL/MADC//MADC_Interface.h"
#include "MCAL/MGIE//MGIE_Interface.h"



#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "util/delay.h"

static u32 Digital_INPUT[2];
static u32 Analog_OUT[2];
static s8 Flag =0;

xSemaphoreHandle ADCSem;

void ADC_SetNotification(void);
void APP_ADC_read(void*pv);
void APP_POT1_CALC(void*pv);		//PINA0
void APP_LM35_CALC(void*pv);		//PINA7;
void APP_LCD_Display(void*pv);

int main(void)
{
	u8 Welcome[]="Welcome";
	//LCD init with welcome massege
	HCLCD_Vid4Bits_Init();
	HCLCD_VidWriteString_4Bits(Welcome);

	_delay_ms(1000);

	HCLCD_VidWriteCommand_4Bits(0x01>>4);
	HCLCD_VidWriteCommand_4Bits(0x01);

	//ADC init
	MADC_VidSetCallBack(ADC_SetNotification);
	MADC_VidADCInterruptEnable();
	MADC_VidInit();
	MADC_u16ADC_StartConversion_With_Interrupt(0);

	MGIE_VidEnable();

	ADCSem = xSemaphoreCreateCounting(1,0);  // init as take Semaphore

	xTaskCreate(APP_ADC_read ,NULL,  100,NULL,0,NULL);
	xTaskCreate(APP_POT1_CALC,NULL,  250,NULL,1,NULL);
	xTaskCreate(APP_LM35_CALC,NULL,  250,NULL,2,NULL);
	xTaskCreate(APP_LCD_Display,NULL,250,NULL,3,NULL);
	vTaskStartScheduler();

	while(1)
	{


	}

	return 0;
}


 void ADC_SetNotification(void)
 {
	 xSemaphoreGive(ADCSem);
 }
 void APP_ADC_read(void*pv)
 {
	 u8 LOC_u8SemState =0;

	 while(1)
	 {
		 LOC_u8SemState= xSemaphoreTake(ADCSem,5);
		 if(LOC_u8SemState == pdPASS)
		 {
			 switch(Flag)
			 {
			 case 0: Digital_INPUT[Flag] =MADC_u16ADCRead();
			 	 	 Flag=7;
			 	 	MADC_u16ADC_StartConversion_With_Interrupt(Flag);
			 	 	 break;
			 case 7: Digital_INPUT[Flag-6] =MADC_u16ADCRead();
			 	 	 Flag=0;
			 	 	MADC_u16ADC_StartConversion_With_Interrupt(Flag);
			 		 break;

			 }
		 }
		 else
		 {

		 }
		 vTaskDelay(10);
	 }
 }
 void APP_LCD_Display(void*pv)
 {
	 u8  str3[] ="tem=";
	 u8  str4[] ="degree";
	 u8  str1[] ="Res=";
	 u8  str2[] ="_--_";
	 HCLCD_VidSetPosition_4BitsMode(1,0);
	 HCLCD_VidWriteString_4Bits(str1);
	 HCLCD_VidSetPosition_4BitsMode(1,9);
	 HCLCD_VidWriteString_4Bits(str2);
	 HCLCD_VidSetPosition_4BitsMode(2,0);
	 HCLCD_VidWriteString_4Bits(str3);
	 HCLCD_VidSetPosition_4BitsMode(2,9);
     HCLCD_VidWriteString_4Bits(str4);


	 while(1)
	 {

		 HCLCD_VidSetPosition_4BitsMode(2,4);
		 HCLCD_VidWriteNumber_4Bits(Analog_OUT[1]);
		 HCLCD_VidSetPosition_4BitsMode(1,4);
		 HCLCD_VidWriteNumber_4Bits(Analog_OUT[0]);

		 vTaskDelay(100);
	 }
 }

  void APP_POT1_CALC(void*pv)
  {
	  while(1)
	  	 {
		  Analog_OUT[0] = (( Digital_INPUT[0]*10000)/ 1023);
	  	  vTaskDelay(11);
	  	 }

  }


  void APP_LM35_CALC(void*pv)
  {
	  while(1)
	  	  	 {
	  		  Analog_OUT[1] = (( Digital_INPUT[1] *5000UL)/1024);
	  		 Analog_OUT[1] =Analog_OUT[1]/10;
	  	  	  vTaskDelay(11);
	  	  	 }

  }
