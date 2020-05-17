/*Author : A7md Salama
*/

#include "gpiolcfg.h"


str_PinConfig_t arr_PinCfg[PINS_NUM] =
{
    {GPIOB_CLOCK , GPIOB , Pin8 , MEDIUM_SPEED , IO_AF , AF_4 , PULL_UP , PUSH_PULL},
	{GPIOB_CLOCK , GPIOB , Pin9 , MEDIUM_SPEED , IO_AF , AF_4 , PULL_UP , PUSH_PULL},
	{GPIOB_CLOCK , GPIOB , Pin10 , MEDIUM_SPEED , IO_AF , AF_4 , PULL_UP , PUSH_PULL},
    {GPIOB_CLOCK , GPIOB , Pin11 , MEDIUM_SPEED , IO_AF , AF_4 , PULL_UP , PUSH_PULL}
};
