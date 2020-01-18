/*
 * sevenSeg.c
 *
 * Created: 18-Jan-20 12:23:24 PM
 *  Author: ahmed
 */ 
#include "sevenSeg.h"
#include "gpio.h"
#include "registers.h"
#include "sevenSegConfig.h"
#include "softwaredelay.h"

void sevenSegInit(En_SevenSegId_t a_segment_id){
	
	switch(a_segment_id){
		
		case SEG_0:
			gpioPinDirection(GPIOB,BIT0,HIGH);
			gpioPinDirection(GPIOB,BIT1,HIGH);
			gpioPinDirection(GPIOB,BIT2,HIGH);
			gpioPinDirection(GPIOB,BIT3,HIGH);
			break;
			
		case SEG_1:
			gpioPinDirection(GPIOB,BIT0,HIGH);
			gpioPinDirection(GPIOB,BIT1,HIGH);
			gpioPinDirection(GPIOB,BIT2,HIGH);
			gpioPinDirection(GPIOB,BIT3,HIGH);
			break;
	}
}

void sevenSegEnable(En_SevenSegId_t en_segment_id){
	
	switch(en_segment_id){
		
		case SEG_0:
			gpioPinDirection(GPIOD,BIT2,HIGH);
			gpioPinWrite(GPIOD,BIT2,HIGH);
			break;
			
		case SEG_1:
			gpioPinDirection(GPIOD,BIT3,HIGH);
			gpioPinWrite(GPIOD,BIT3,HIGH);
			break;
	}
}

void sevenSegDisable(En_SevenSegId_t en_segment_id){
	
	switch(en_segment_id){
		
		case SEG_0:
			gpioPinWrite(GPIOD,BIT2,LOW);
			break;
			
		case SEG_1:
			gpioPinWrite(GPIOD,BIT3,LOW);
			break;
	}
}

void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number){
	
	switch(en_segment_id){
		
		case SEG_0:
			
				break;
				
		case SEG_1:
			break;
	}
	
	if((u8_number & BIT0) != 0)
		gpioPinWrite(GPIOB,BIT0,HIGH);
	else
		gpioPinWrite(GPIOB,BIT0,LOW);
	if((u8_number & BIT1) != 0)
		gpioPinWrite(GPIOB,BIT1,HIGH);
	else
		gpioPinWrite(GPIOB,BIT1,LOW);
	if((u8_number & BIT2) != 0)
		gpioPinWrite(GPIOB,BIT2,HIGH);
	else
		gpioPinWrite(GPIOB,BIT2,LOW);
	if((u8_number & BIT3) != 0)
		gpioPinWrite(GPIOB,BIT3,HIGH);
	else
		gpioPinWrite(GPIOB,BIT3,LOW);

}