
#include <stdio.h>
#include "CarSM.h"

/*Car SM init Test*/
void Car_SM_TEST()
{
    /*1st Test Case:
    *Description : Everything done as expected
    *Expected OUT : E_OK
    *Output : E_OK
    */

   printf("%d  ",Car_SM_Init());

   /*2nd test case:
   *Description : Multiple Init
   *Expected out : ERROR_MULTIPLE_INIT
   *Output : ERROR_MULTIPLE_INIT
   */

  Car_SM_Init();
  printf("%d",Car_SM_Init());

}

void Car_Update_Test()
{
    /*1st test case:
    *Description: Everything done as expected
    *Expected out : E_OK
    *Output : E_OK
    */
    Car_SM_Init();
    printf("%d",Car_SM_Update());

    /*2nd test case:
    *Description : updating without init
    *Expected out : Error
    *Output:Error
    */
   printf("%d",Car_SM_Update());
}


int main()
{
    Car_Update_Test();
    return 0;
}