/*
 * CFile1.c
 *
 * Created: 17-Jan-20 5:54:45 PM
 *  Author: ahmed
 */ 
#include "std_types.h"
#include "softwaredelay.h"

void delay_ms(uint8_t delay){
	
	uint32_t ms_tick,total_ticks;
	for(total_ticks=0;total_ticks<delay;total_ticks++){
		
		for(ms_tick=0 ; ms_tick<2290 ;ms_tick++);
	}	
	
}