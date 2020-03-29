/*
 * CarSM.c
 *
 * Created: 29-Mar-20 11:40:34 AM
 *  Author: ahmed
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
#include "CarSM.h"
#include "Us.h"
//#include "Steering.h"

/************************************************************************/
/*							DEFINES                                      */
/************************************************************************/
#define CAR_STOP	(5)
#define CAR_STOP_SPEED	(0)
#define CAR_SPEED	  (30)
#define DISTANCE_25   (25)
#define DISTANCE_45   (45)

#define FORWARD		(0)
#define BACKWARD	(1)
#define LEFT		(2)
#define INIT_DIR	(3)

#define CAR_INITALIZED	(1)
#define CAR_NOT_INIT	(0)


/************************************************************************/
/*							GLOBALS                                      */
/************************************************************************/
static uint16_t gu16_CarDistance = ZERO;
static uint8_t gu8_CarState = CAR_NOT_INIT;


/*CarTask
*Input : None
*Output : None
*Description : function that initalize all Drivers used by Car state machine function
*/

ERROR_STATUS Car_SM_Init(void)
{
	/*create error flag*/
	ERROR_STATUS ERROR_STATE = E_OK;
	
	/*check for multiple inits*/
	if(gu8_CarState == CAR_NOT_INIT)
	{
		/*init US*/
		ERROR_STATE = Us_Init();
		
		/*init motors*/
		//ERROR_STATE = Steering_Init(void);
		
		/*if there's no error then initialize car*/
		if(ERROR_STATE == E_OK)
		{
			gu8_CarState = CAR_INITALIZED;
		}	
	}
	
	else
	{
		ERROR_STATE = ERROR_CAR_BASE + ERROR_MULTIPLE_MODULE_INIT; 
	}
	
	return ERROR_STATE;
}

/*CarSM Task
*Inputs : None
*Output : None
*Description : Task function ran by SOS and at which car decission is being taken
.. for more than 30 CM car goes forward , between 30 and 15 cm car turns right
for less then 15 cm car goes backward
*/

ERROR_STATUS Car_SM_Update(void)
{
	/*Create error flag*/
	ERROR_STATUS ERROR_STATE = E_OK;
	
	if(gu8_CarState == CAR_INITALIZED)
	{
		/*first we will send trigger to ultra sonic*/
		ERROR_STATE = Us_Trigger();
		
		/*we will read the distance measure by US*/
		ERROR_STATE = Us_GetDistance(&gu16_CarDistance);
		
		/*check for errors then stop car if error received*/
		if(ERROR_STATE != E_OK)
		{
			/*Stop the car*/
			//Steering_SteerCar(CAR_STOP , CAR_STOP_SPEED)
		}

		else
		{
			if(gu16_CarDistance > DISTANCE_45)
			{
				//ERROR_STATE = Steering_SteerCar(FORWARD , CAR_SPEED);
			}
			
			else if(gu16_CarDistance < DISTANCE_45 && gu16_CarDistance > DISTANCE_25)
			{
				//ERROR_STATE = Steering_SteerCar(LEFT , CAR_SPEED);
			}
			
			else if(gu16_CarDistance < DISTANCE_25)
			{
				//ERROR_STATE = Steering_SteerCar(BACKWARD,CAR_SPEED);
			}
			
		}
	}
	
	else
	{
		ERROR_STATE = ERROR_CAR_BASE + ERROR_MODULE_NOT_INIT;	
	}
	
	return ERROR_STATE;	
}