/*
 * software_delay.c
 *
 * Created: 19-Feb-20 1:22:01 AM
 *  Author: ahmed
 */ 
#include "software_delay.h"

/************************************************************************/
/*			DEFINES                                                      */
/************************************************************************/
#define MS_TICKS (400)

/************************************************************************/
/*						APIS                                            */
/************************************************************************/

/*
**Description: function to delay for some mSeconds
*@parm : delay_ms : number of mSeconds to block for
*/
ERROR_STATUS software_delay(uint16_t delay_ms){
	
	ERROR_STATUS error_flag = E_OK;
	
	/*Defines of loop variables*/	
	uint16_t u16_delayLoop = 0;
	uint16_t u16_Msdelayloop=0;
	
	
	/*delay for delay_ms time, MS_TICKS .. number of ticks for 1 ms*/
	for(u16_delayLoop = 0;u16_delayLoop<delay_ms;u16_delayLoop++){
		
	for(u16_Msdelayloop = 0;u16_Msdelayloop<MS_TICKS ; u16_Msdelayloop++);
	}
	
	return error_flag;
}
