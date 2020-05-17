/*Author : A7md Salama
*/
/*create Structure of clock configs*/
#include "./SERVICES/std_types.h"

/*Defines*/
#define HSE 0

/*Please define HSI if you want to use it as pll source*/
#ifdef HSI_PLL
#define PLL_N_MULTIPLICATION_FACTOR (1u)

#else
#define PLL_N_MULTIPLICATION_FACTOR (2u)
#endif


typedef struct{
    uint8_t Clock_Source;
    uint8_t Clock_Frequency_MHZ;
}str_ckInit_t;


volatile extern str_ckInit_t str_ck_init;
