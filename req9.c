/*
 * req9.c
 *
 * Created: 18-Jan-20 2:29:13 PM
 *  Author: ahmed
 */ 
#include "req9.h"
#include "gpio.h"
#include "registers.h"
#include "softwaredelay.h"

state_machine state1;

void app_Ledstate(state_machine en_machine){
	
	switch(en_machine){
		
		case GO:
			gpioPinDirection(GPIOA,BIT0,HIGH);
			gpioPinWrite(GPIOA,BIT0,HIGH);
			gpioPinWrite(GPIOA,BIT1,LOW);
			gpioPinWrite(GPIOA,BIT2,LOW);
			break;
		
		case STOP:
			gpioPinDirection(GPIOA,BIT2,HIGH);
			gpioPinWrite(GPIOA,BIT2,HIGH);
			gpioPinWrite(GPIOA,BIT1,LOW);
			gpioPinWrite(GPIOA,BIT0,LOW);
			break;
			
		case GETREADY:
			gpioPinDirection(GPIOA,BIT1,HIGH);
			gpioPinWrite(GPIOA,BIT1,HIGH);
			gpioPinWrite(GPIOA,BIT2,LOW);
			gpioPinWrite(GPIOA,BIT0,LOW);
			break;
	}
}

void app_ledcycle(void){
	
	int loop;
	for(loop=0;loop<4;loop++){
		
		app_Ledstate(loop);
		delay_ms(1000);
	}
}