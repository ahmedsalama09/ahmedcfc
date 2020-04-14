/*
 * software_delay.h
 *
 * Created: 19-Feb-20 1:22:48 AM
 *  Author: ahmed
 */ 


#ifndef SOFTWARE_DELAY_H_
#define SOFTWARE_DELAY_H_

/************************************************************************/
/*				INCLUDES                                                */
/************************************************************************/
#include "std_types.h"

/*
**Description: function to delay for some mSeconds
*@parm : delay_ms : number of mSeconds to block for
*/
extern ERROR_STATUS software_delay(uint16_t delay_ms);

#endif /* SOFTWARE_DELAY_H_ */