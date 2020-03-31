/*author Ahmed Salama
*/

void project_IntegrationTesting(int* ptr1, int* ptr2, int size)
{
	ERROR_STATUS ReturnedValue = copyArray(ptr1, ptr2, size);
	int i, variable;

	if(ReturnedValue == MODULE1_E_NULL_POINTER)
	{
		printf("Module 1 Error Detected, Null Pointer\n");
	}else if(ReturnedValue == MODULE1_E_INVALID_SIZE)
	{
		printf("Module 1 Error Detected, Invalid Size\n");
	}else if(ReturnedValue == MODULE2_E_NULL_POINTER)
	{
		printf("Module 2 Error Detected, Null Pointer\n");
	}else if(ReturnedValue == MODULE2_E_INVALID_SIZE)
	{
		printf("Module 2 Error Detected, Invalid Size\n");
	}else
	{
		for(i=0 ; i<size ; i++)
		{
			if(ptr1[i] == ptr2[i])
			{
				variable = 1;
			}
			else
			{
				variable = 0;
				break;
			}
		}

		if(variable == 1)
		{
			printf("Project No Errors\n");
		}else if(variable == 0)
		{
			printf("Project Error Detected, Error In Functionality\n");
		}else
		{
			/* Do Nothing */
		}
	}
}
