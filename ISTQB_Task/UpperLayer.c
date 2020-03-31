/*author : Ahmed Salama
*/

#include "UpperLayer.h"
#include "First_Proj.h"

ERROR_STATUS Copy_array(uint16_t *arr1, uint16_t *arr2, uint8_t size)
{
    ERROR_STATUS ERR_STATE = E_OK;

    uint8_t u8_counter = ZERO;

    if(arr1 == NULL || arr2 == NULL)
    {
        ERR_STATE = ERROR_NULL_PTR_INIT;
    }
    else if(size < MINIMUM_ARRAY_SIZE || size > MAXIMUM_ARRAY_SIZE)
    {

        ERR_STATE = ERROR_INVLAID_VALUE;
    }
    else
    {
		for(u8_counter=0 ; u8_counter<size ; u8_counter++)
		{
			/* Copy each element in array2 to array1 */
			*arr2 = *arr1;
			/* Increment both pointers to get the next array element */
			arr1++;
			arr2++;
		}
    ERR_STATE = array_Print(arr2,size);

    return ERR_STATE;
}