/*author : a7md Salama
*/

/*includes*/
//#include "_stdint.h"
#include "Clock.h"
#include "Clocklcfg.h"
#include "PerRegs.h"

/*Defines*/
#define MAX_CLOCK_MHZ (168)
#define MIN_CLOCK_MHZ (50)

/*CR Defines*/
#define RCC_HSEREADY    (0x00010000u)
#define RCC_HSEON   	(0x00020000u)
#define RCC_CSS_ON  	(0x80000000u)
#define RCC_HSION    	(0x00000001u)
#define RCC_HSIREADY 	(0x00000002u)
#define RCC_PLL_READY    (0x02000000u)
#define RCC_PLL_ON 	 	(0x01000000u)
#define RCC_PLLI2S_ON   (0x04000000u)
#define RCC_PLLSAI_ON   (0x10000000u)

/*Clock Source Macro*/
#define RCC_SW_HSI (0x00000000u)
#define RCC_SW_HSE (0x00000001u)
#define RCC_SW_PLL (0x00000002u)
#define RCC_SW_MASK (0x00000003u)

/*PLL Factors*/
#define PLL_P_MASK 	 (0x00030000u)
#define PLL_M_MASK	 (0x0000003Fu)
#define PLL_N_MASK   (0x00007FC0u)

#define PLL_P_FACTOR (0x00000000u)

#define PLL_M_FACTOR (0x00000008u)
#define PLL_MAX_N_FACTOR (511u)

#define PLL_N_FACTOR_MASK (0x1FFu)
#define PLL_N_FACTOR_SHIFT (6u)
#define PLL_N_MULTIPLICATION_FACTOR (2u)

#define PLL_HSE_SOURCE (0x400000)

#define PLL_ON  (0x1000000)
#define PLL_READY (0x2000000)
 
#define RCC_PLL_SYSCLOCK (0x02)

/*PLLCFGR source Macros*/
#define RCC_PLLSOURCE_MASK 	 (0x00400000u)
#define RCC_PLLSOURCE_HSE	 (0x00400000u)
#define RCC_PLLSOURCE_HSI	 (0x00000000u)

/*Buses Macros*/
#define RCC_CFGR_AHBPSC_MASK (0x000000F0u)
#define RCC_CFGR_PRE1_MASK   (0x00001C00u)
#define RCC_CFGR_PRE2_MASK   (0x0000E000u)

/*Buses Prescale*/
#define RCC_CFGR_AHBPSC		 (0x00000000u)
#define RCC_CFGR_PB1PSC		 (0x00001400u)
#define RCC_CFGR_PB2PSC		 (0x00008000u)

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
    if((str_ck_init.Clock_Frequency_MHZ > ((uint32_t) MAX_CLOCK_MHZ))  || (str_ck_init.Clock_Frequency_MHZ < ((uint32_t) MIN_CLOCK_MHZ)))
    {
        /*Record error*/
        ERR_STATE = ERROR_SYSTICK_BASE + ERROR_WRONG_CLOCK_VALUE;
    }
    else{

    	/*Create NFACTOR Var*/
    	uint16_t PllN_Factor = 0;

    	/*First enable HSI Clock to replace HSE*/
    	RCC->CR |= RCC_HSION;

    	/*Wait For HSI To be Ready*/
    	while((RCC->CR & RCC_HSIREADY) == 0);

    	/*Clear SW BITS*/
    	RCC->CFGR &= ~RCC_SW_MASK;

    	/*Choose HSI To be Clock Source*/
    	RCC->CFGR |= RCC_SW_HSI;

    	/*Enable HSE*/
    	RCC->CR |= RCC_HSEON;

    	/*Wait for HSE To be Ready*/
    	while((RCC->CR & RCC_HSEREADY) == 0);

    	/*Disable All PLLs*/
    	RCC->CR &= ~(RCC_PLL_ON);
    	RCC->CR &= ~(RCC_PLLSAI_ON);
    	RCC->CR &= ~(RCC_PLLI2S_ON);

    	/*Configure PLL Parameters
    	 * P Fixed = 4 , M Fixed = 2
    	 * N = FPLL OUT
    	 */
    	RCC->CFGR &= ~PLL_P_MASK;
    	RCC->CFGR |= PLL_P_FACTOR;

    	RCC->CFGR &= ~PLL_M_MASK;
    	RCC->CFGR |= PLL_M_FACTOR;

    	PllN_Factor = PLL_N_MULTIPLICATION_FACTOR * str_ck_init.Clock_Frequency_MHZ;

    	PllN_Factor = PllN_Factor & PLL_N_FACTOR_MASK;

    	/*Asign the value to Reg*/
    	RCC->PLLCFGR &= ~PLL_N_MASK;
    	RCC->PLLCFGR |= (PllN_Factor << PLL_N_FACTOR_SHIFT);

    	/*Configure Buses Clocks*/
    	RCC->CFGR &= ~ RCC_CFGR_AHBPSC_MASK;
    	RCC->CFGR |= RCC_CFGR_AHBPSC;

    	RCC->CFGR &= ~RCC_CFGR_PRE1_MASK;
    	RCC->CFGR |= RCC_CFGR_PB1PSC;

    	RCC->CFGR &= ~RCC_CFGR_PRE2_MASK;
    	RCC->CFGR |= RCC_CFGR_PB2PSC;

    	/*Chooose HSE As PLL Source*/
    	RCC->PLLCFGR &= ~ RCC_PLLSOURCE_MASK;
    	RCC->PLLCFGR |= RCC_PLLSOURCE_HSE;

    	/*Enable PLL*/
    	RCC->CR |= RCC_PLL_ON;

    	/*wait for pll to be ready*/
    	while((RCC->CR & RCC_PLL_READY) == 0);

    	/*Choose PLL As Sys Clock*/
    	RCC->CFGR |= RCC_SW_PLL;
    }

    return ERR_STATE;
}
