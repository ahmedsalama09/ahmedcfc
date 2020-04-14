/*Author : A7md Salama
*/
/*create Structure of clock configs*/
#include "../std_types.h"

/*Defines*/
#define HSE 0

typedef struct{
    uint8_t Clock_Source;
    uint8_t Clock_Frequency_MHZ;
}str_ckInit_t;


extern str_ckInit_t str_ck_init;
