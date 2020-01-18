/*
 * pushButton.c
 *
 * Created: 18-Jan-20 10:17:48 AM
 *  Author: ahmed
 */ 
#include "pushButton.h"
#include "registers.h"
#include "gpio.h"
#include "softwaredelay.h"
#include "pushButtonConfig.h"

En_buttonStatus_t g_button0,g_button1,g_button2,g_button3;

void pushButtonInit(En_buttonId_t en_butotn_id){

	/*Check the button you want to configure then configure it
		@PIN  0 ---> GPIOB 0
		 PIN  1----> GPIOB 1
		 PIN  2----> GPIOB 2
		 PIN  3----> GPIOB 3
		 */
	switch(en_butotn_id){
		
		case BTN_0:
			gpioPinWrite(BTN_0_GPIO,BTN_0_BIT,INPUT);
			break;
			
		case BTN_1:
			gpioPinWrite(BTN_1_GPIO,BTN_1_BIT,INPUT);
			break;
		
		case BTN_2:
			gpioPinWrite(BTN_2_GPIO,BTN_2_BIT,INPUT);
			break;
		
		case BTN_3:
			gpioPinWrite(BTN_3_GPIO,BTN_3_BIT,INPUT);
			break;
	}	
}

void pushButtonUpdate(En_buttonId_t en_butotn_id){
		

}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id){
	
	uint8_t status =0,loop=0;
	switch(en_butotn_id){
		
		case BTN_0:
			delay_ms(10);
			status = gpioPinRead(BTN_0_GPIO,BTN_0_BIT);
			return status;
			break;
		
		case BTN_1:
			delay_ms(10);
			status = gpioPinRead(BTN_1_GPIO,BTN_1_BIT);
			delay_ms(50);
			return status;
		break;

	}
	return 0;
}