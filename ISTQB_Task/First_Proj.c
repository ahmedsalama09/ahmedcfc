/*Author : Ahmed Salama
*lower layer project*/

#include <stdio.h>
#include "First_Proj.h"

ERROR_STATUS array_Print(uint16_t *arr, uint8_t size)
{
    ERROR_STATUS ERR_STATE = E_OK;

    uint8_t u8_Counter = ZERO;

    if(arr == NULL)
    {
        ERR_STATE = ERROR_NULL_PTR_INIT;
    }

    else if( size < MINIMUM_ARRAY_SIZE || size > MAXIMUM_ARRAY_SIZE)
    {
        ERR_STATE = ERROR_INVLAID_VALUE;
    }
    else
    {
        /* printf elements */
        for(u8_Counter ; u8_Counter < size ; u8_Counter++)
        {
            printf("%u",arr[u8_Counter]);
        }
    }

    return ERR_STATE;
}
