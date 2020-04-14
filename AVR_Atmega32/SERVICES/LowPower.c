/*
 * LowPower.c
 *
 * Created: 10-Mar-20 8:06:09 PM
 *  Author: ahmed
 */ 

/************************************************************************/
/*							INCLUDES								    */
/************************************************************************/
#include "LowPower.h"
#include "/Sprint projects/SOS&CarApp/Car by sos/MCAL/interrupt.h"

/************************************************************************/
/*						DEFINES                                         */
/************************************************************************/

/*to enter sleep mode, an assembly instruction written to write it*/
void Sleep_Mode(void)
{
		__asm__ __volatile__ ("sleep" "\n\t"::);
		
		SET_BIT(MCUCR,7);
}