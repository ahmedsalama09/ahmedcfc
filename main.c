/*
 * GccApplication1.c
 *
 * Created: 17-Jan-20 1:12:11 PM
 * Author : ahmed
 */ 

#include <avr/io.h>
#include "registers.h"
#include "std_types.h"
#include "gpio.h"
#include "softwaredelay.h"
#include "led.h"
#include "sevenSeg.h"
#include "req9.h"
#include "pushButton.h"

/*INFOS PLEASE READ:
the requirements from 7:9 are blow and they're commented
I HAVE A PROBLEM WITH SIMULATION TIMING>> simulator isn't working fine with it, it makes undefined behaviour
*/

int main(void)
{

	
	/*REQ9 Example
	while(1){
	for(u8_stateloop=0;u8_stateloop<4;u8_stateloop++){
	app_Ledstate(u8_stateloop);
	delay_ms(1000);
	}
	u8_stateloop=0;
	}
	*/

    while (1) 
    {
		/*REQ7 Example @ 7segment*
		uint8_t u8_counter;
		uint32_t u32_delay;
		while(u8_counter <= 99){
			
			sevenSegEnable(SEG_0);
			sevenSegWrite(SEG_0,((u8_counter/10)%10));
			delay_ms(1);
			sevenSegDisable(SEG_0);
			
			sevenSegEnable(SEG_1);
			sevenSegWrite(SEG_1,((u8_counter/10)%10));
			delay_ms(1);
			sevenSegDisable(SEG_1);
			u32_delay++;
			
			if(u32_delay % 469 == 0)
				u8_counter++;
		}*/
		
		/* REQ8 Example @ LEDS BLINKING*/
		/*uint8_t u8_loop1,u8_loop2,u8_nobounce=0;
		if(pushButtonGetStatus(BTN_0) == Pressed){
			while(pushButtonGetStatus(BTN_0) != Released);
			gpioPinWrite(GPIOA,BIT0,HIGH);
			for(u8_loop1=0;u8_loop1<1000;u8_loop1++){
				for(u8_loop2=0;u8_loop2<2290;u8_loop2++){
					
					if((u8_nobounce < 1) && (pushButtonGetStatus(BTN_0) == Pressed)){
						delay_ms(1000);
						u8_nobounce++;}
				}
			}
		gpioPinWrite(GPIOA,BIT0,LOW);
		
		}*/
			
	}
}

