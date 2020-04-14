/*Author : Ahmed Salama
*/

#include "MCU_hw.h"

/*Adresses Defines of registers*/
#define SCB_BASE    (0xE000ED00)
#define NVIC_BASE   (0x0E000E100)   
#define SYSTICK_BASE  (0xE000E010)  

str_NVIC volatile *NVIC = (str_NVIC *) NVIC_BASE;
str_SCB volatile *SCB = (str_SCB *) SCB_BASE;
str_Systick volatile *SYSTICK = (str_Systick *) SYSTICK_BASE;
