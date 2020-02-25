/*
 * tmuapp.c
 *
 * Created: 24-Feb-20 11:26:07 AM
 * Author : ahmed
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
//#include <avr/io.h>
#include "/tmu/tmuapp/tmuapp/SERVICE/TMU.h"
#include "/tmu/tmuapp/tmuapp/MCAL/DIO.h"

/************************************************************************/
/*					DEFINES                                             */
/************************************************************************/
#define MSECONDS_1000	(1000)
#define MSECONDS_500	(500)

#define TASK_ID_1		(1)
#define TASK_ID_2		(2)
/************************************************************************/
/*						DECLARATIONS	                                */
/************************************************************************/
void LED_Toggle(void);
void LED_Toli(void);

/************************************************************************/
/*					MAIN                                                */
/************************************************************************/

/** APPLICATION
*	Description
** a small application of two toggles one of them is done once"one shot" 
other is done periodicly 
*/
int main(void)
{
	DIO_Cfg_s m;
	m.GPIO = GPIOA;
	m.dir = OUTPUT;
	m.pins = LOWER_NIBBLE;
	DIO_init(&m);
	
	st_TMU_init s;
	s.u8_timer_chnl = TMU_TMR_CH0;
	
	/************************************************************************/
	/*			TASKS INITS                                                 */
	/************************************************************************/
	TMU_TaskType p;
	p.u32_counts = MSECONDS_1000;
	p.task_ptr =LED_Toggle; 
	p.u8_id = TASK_ID_1;
	p.u8_periodic_state = TMU_PERIODIC;
	
	TMU_Init(&s);
	TMU_Start_Timer(&p);
	p.u32_counts = MSECONDS_500;
	p.task_ptr =LED_Toli;
	p.u8_id = TASK_ID_2;
	p.u8_periodic_state = TMU_ONESHOOT;
	TMU_Start_Timer(&p);
	
 
    while (1) 
    {
		/*start dispatcher*/
		TMU_Dispatch();
		
	}
}

void LED_Toggle(void)
{
	DIO_Toggle(GPIOA,BIT0);
}

void LED_Toli(void)
{
	DIO_Toggle(GPIOA,BIT1);

}