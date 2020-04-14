/*
 * Error_table.h
 *
 * Created: 25-Feb-20 5:22:48 PM
 *  Author: ahmed
 */ 


#ifndef ERROR_TABLE_H_
#define ERROR_TABLE_H_

/************************************************************************/
/*							DIO DEFINES                                */
/************************************************************************/
#define ERROR_DIO_BASE  (-11)
#define ERROR_INVALID_PORT  (-1)
#define ERROR_INVALID_DIRECTION (-2)
#define ERROR_INVLAID_VALUE (-3)
#define ERROR_DIO_NOT_INIT  (-4)

/************************************************************************/
/*							TIMER DEFINES                                */
/************************************************************************/
#define ERROR_TIMER_BASE    (-20)
#define ERROR_WRONG_CHANNEL (-1)
#define ERROR_WRONG_CONFIG  (-2)
#define ERROR_INVALID_COUNTS (-3)
#define ERROR_INVALID_PRESCALLER (-4)
#define ERROR_TIMER_NOT_INIT (-5)

/************************************************************************/
/*							ICU DEFINES                                 */
/************************************************************************/
#define ERROR_ICU_BASE  (-30)
#define ERROR_CHANNEL_NOT_IMPLEMENTED (-3)
#define ERROR_TIMER_NOT_IMPLEMENTED (-4)
#define ERROR_MODULE_NOT_INIT   (-5)

/************************************************************************/
/*							US DEFINES                                  */
/************************************************************************/
#define ERROR_US_BASE	(-40)

/************************************************************************/
/*							CAR DEFINES                                 */
/************************************************************************/
#define ERROR_CAR_BASE (-50)
#define ERROR_TRIGGER_NOT_SENT (-4)


/************************************************************************/
/*							INIT DEFINES                                */
/************************************************************************/
#define ERROR_NULL_PTR_INIT		(-1)
#define ERROR_MULTIPLE_MODULE_INIT	(-2)
#define INVALID_INIT_PARAMETER		(-3)

/************************************************************************/
/*							START DEFINES                               */
/************************************************************************/
#define ERROR_NULL_PTR_START	(-4)
#define ERROR_MULTIPLE_MODULE_START	(-5)
#define ERROR_START_FULL_BUFFER		(-6)
#define ERROR_MODULE_PRIORITY_USED	(-7)
#define ERROR_INVALID_START_PARAMETERS	(-11)
/************************************************************************/
/*							DISPATCH DEFINES                            */
/************************************************************************/
#define ERROR_DISPATCH_NO_TASKS	(-8)

/************************************************************************/
/*							STOP DEFINES                                */
/************************************************************************/
#define ERROR_MODULES_STOPPED_BEFORE	(-9)
#define ERROR_MODULE_DIDNOT_START		(-10)


#endif /* ERROR_TABLE_H_ */
