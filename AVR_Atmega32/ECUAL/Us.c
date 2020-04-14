/*
 * Us.c
 *
 * Created: 18-Feb-20 4:43:20 PM
 *  Author: ahmed
 */ 
#include "Us.h"
#include "/Sprint projects/SOS&CarApp/Car by sos/MCAL/DIO.h"
#include "/Sprint projects/SOS&CarApp/Car by sos/ECUAL/ICU.h"
#include <util/delay.h>

/************************************************************************/
/*				   Defines					                            */
/************************************************************************/
#define LOOP_VAL   (200)
#define US_NOT_INIT	(0)
#define US_INIT	(1)
#define TRIGGER_DELAY_TICKS	(12)

/*Each cm takes 58 microsecond time*/
#define CM_MICROSECOND	(58)

/************************************************************************/
/*						GLOBALS                                         */
/************************************************************************/
static uint8_t gu8_UsInit_State = US_NOT_INIT;

/************************************************************************/
/*					APIS                                                */
/************************************************************************/

/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/

ERROR_STATUS Us_Init(void){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*check if us was initialized or not*/
	if(gu8_UsInit_State == US_NOT_INIT)
	{
		/*create DIO struct to configure it*/
		st_DIO_Cfg_t st_DioUs;
		
		/*configure PC7 as output echo pin*/
		st_DioUs.dir = OUTPUT;
		st_DioUs.GPIO = GPIOC;
		st_DioUs.pins = PIN7;
		
		/*init DIO*/
		error_flag = DIO_init(&st_DioUs);
		
		/*if there's error with DIO.. Don't init*/
		if(error_flag == E_OK)
		{
			/*create ICU struct to configure it*/
			Icu_cfg_s st_IcuUs_t;
			
			/*use PB2/IRQ as input && timer 0*/
			st_IcuUs_t.ICU_Ch_No = ICU_CH2;
			st_IcuUs_t.ICU_Ch_Timer = ICU_TIMER_CH2;
			
			/*init ICU*/
			error_flag = Icu_Init(&st_IcuUs_t);
			
			/*check if there's no error then save init state*/
			if(error_flag == E_OK)
			{
				gu8_UsInit_State = US_INIT;
			}
		}	
	}
	
	else
	{
		/*save multiple init error*/
		error_flag = ERROR_US_BASE + ERROR_MULTIPLE_MODULE_INIT;
	}
	
	return error_flag;
}

/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*chekc if initalized or not*/
	if(gu8_UsInit_State == US_INIT)
	{
		/*send pulse on P7 for some time */
		error_flag = DIO_Write(GPIOC,PIN7,HIGH);
		
		/*delay 12 microS to send the trigger*/
		_delay_us(TRIGGER_DELAY_TICKS);
		
		error_flag = DIO_Write(GPIOC,PIN7,LOW);
	}
	else
	{
		/*save error status*/
		error_flag = ERROR_US_BASE + ERROR_MODULE_NOT_INIT;
	}
	
	return error_flag;
}

/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/

ERROR_STATUS Us_GetDistance(uint16_t *Distance){
	
	/*create status flag*/
	ERROR_STATUS error_status = E_OK;
	
	/*check for init*/
	if(gu8_UsInit_State == US_INIT)
	{
		/*variable to read time*/
		uint32_t u32_time_Us = ZERO;
		
		/*check distance pointer*/
		if(Distance == NULL){
			
			/*null pointer isn't valid*/
			error_status = ERROR_US_BASE + ERROR_NULL_PTR_INIT;
		}
		
		else{
			/*read time value*/
			error_status = Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&u32_time_Us);
			
			/*calculate distance*/
			*Distance = (u32_time_Us/CM_MICROSECOND);
		}
	}
	else
	{
		/*save error not init*/
		error_status = ERROR_US_BASE + ERROR_MODULE_NOT_INIT;
	}
	
	
	/*return E_OK*/
	return error_status;
}

ERROR_STATUS Us_DistanceState(uint8_t *ISR_Status)
{
	ERROR_STATUS ERR_STATE = E_OK;
	
	ERR_STATE = ICU_ISR_Status(*ISR_Status);
	
	return ERR_STATE;
	
}