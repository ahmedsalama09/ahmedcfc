/*
 * CarSM.h
 *
 * Created: 29-Mar-20 11:40:48 AM
 *  Author: ahmed
 */ 


#ifndef CARSM_H_
#define CARSM_H_

/************************************************************************/
/*							INCLUDES                                   */
/************************************************************************/
#include "Error_table.h"
#include "std_types.h"
#include "common_macros.h"

/************************************************************************/
/*							DECLARATIONS                                */
/************************************************************************/
/*CarTask
*Input : None
*Output : None
*Description : function that initalize all Drivers used by Car state machine function
*/

ERROR_STATUS Car_SM_Init(void);

/*CarSM Task
*Inputs : None
*Output : None
*Description : Task function ran by SOS and at which car decission is being taken
.. for more than 30 CM car goes forward , between 30 and 15 cm car turns right
for less then 15 cm car goes backward
*/

ERROR_STATUS Car_SM_Update(void);




#endif /* CARSM_H_ */