
#ifndef __FIRST_PROJ_H
#define __FIRST_PROJ_H

#include "Error_table.h"
#include "std_types.h"
#include "common_macros.h"

#define MINIMUM_ARRAY_SIZE 1
#define MAXIMUM_ARRAY_SIZE 18


/*function to print array and check for any error*/
ERROR_STATUS array_Print(uint16_t *arr, uint8_t size);

#endif