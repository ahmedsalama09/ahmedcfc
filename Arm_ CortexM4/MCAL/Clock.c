/*author : a7md Salama
*/

/*includes*/
#include "../std_types.h"
#include "Clock.h"
#include "Clocklcfg.h"
#include "PerRegs.h"

/*Defines*/
#define MAX_CLOCK_MHZ (168)
#define RCC_HSEREADY    (0x20000)
#define RCC_HSEON   (0x10000)
#define RCC_CSS_ON  (0x80000)
#define RCC_HSION   (0x01)
#define RCC_HSIREADY (0x02)
/*P = 4 and M =2*/
#define PLL_P_FACTOR (0x00010000)
#define PLL_M_FACTOR (0x00000002)
#define PLL_MAX_N_FACTOR (511)

#define PLL_HSE_SOURCE (0x400000)

#define PLL_ON  (0x1000000)
#define PLL_READY (0x2000000)
 
#define RCC_PLL_SYSCLOCK (0x02)

/*Buses Prescal*/
#define RCC_APB2_90MHZ_FACTOR (0x04)
#define RCC_APB1_45MHZ_FACTOR (0x05)


/*APIS*/

/*ClockInit
*Description : function that inits clock with desired frequency
*Input : None
*Output : ERROR if found
*/
ERROR_STATUS Clock_init(void)
{
    /*Create ERROR FLAG*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Check for Clock Value*/
    if(str_ck_init.Clock_Frequency_MHZ > ((uint32_t) MAX_CLOCK_MHZ))
    {
        /*Record error*/
        ERR_STATE = ERROR_SYSTICK_BASE + ERROR_WRONG_CLOCK_VALUE;
    }
    else{

        /*Create N Factor Var*/
        uint16_t PLL_N_Factor;

        /*Clear CR REG first*/
        RCC->CR = ZERO;

        /*Enable HSE and HSI*/
        RCC->CR |= (uint32_t) RCC_HSION;
        while((RCC->CR & ((uint32_t)RCC_HSIREADY)) == ZERO);

        /*wait for RCC Ready Flag*/
        RCC->CR |= (uint32_t) RCC_HSEON;
        while((RCC->CR & ((uint32_t)RCC_HSEREADY)) == ZERO);

        /*Enable CSS*/
        RCC->CR |= RCC_CSS_ON;

        /*Set PLL Parameters*/
        /*P=4 Factor and M = 2*/
        RCC->PLLCFGR = ZERO;
        RCC->PLLCFGR |= (((uint32_t)PLL_P_FACTOR) | ((uint32_t)PLL_M_FACTOR)); 

        /*Calculate N Factor*/
        PLL_N_Factor = (8 * str_ck_init.Clock_Frequency_MHZ)/ 8;

        if(PLL_N_Factor > PLL_MAX_N_FACTOR)
        {
            ERR_STATE = ERROR_SYSTICK_BASE +  ERROR_WRONG_N_FACTOR;
        }
        else
        {
            /* assign  N_Fact value */
            RCC->PLLCFGR |= (PLL_N_Factor << 6);
        }

        /*Choose HSE AS PLL Source*/
        RCC->PLLCFGR |= (uint32_t)PLL_HSE_SOURCE;
        
        /*Enable PLL and wait till it's enabled*/
        RCC->CR |= (uint32_t) PLL_ON;
        while((RCC->CR & PLL_READY) == ZERO);

        /*Choose PLL As Sys Clock*/
        RCC->CFGR |= (uint32_t) RCC_PLL_SYSCLOCK;

        /*SET APB1,APB2 Speeds*/
        RCC->CFGR |= (uint32_t)((RCC_APB1_45MHZ_FACTOR << 10) | (RCC_APB2_90MHZ_FACTOR << 13));

    }

    return ERR_STATE;
}
