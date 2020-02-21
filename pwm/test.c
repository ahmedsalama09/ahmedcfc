/*
 * test.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Youssef Harby
 */


#include <stdio.h>
#include "PWM_TS/PWM.h"

Pwm_Cfg_s cfg_test;

void PWM_initTesting(uint8_t channel, uint8_t ExpectedOutput)
{
	static int initTestCounter = 1;
	uint8_t output;

	cfg_test.Channel = channel;
	cfg_test.Prescaler = 0;

	output = Pwm_Init(&cfg_test);

	if(output == ExpectedOutput)
	{
		printf("PWM_init test %d Passed\n", initTestCounter);
		fflush(stdout);
	}else
	{
		printf("PWM_init test %d failed\n", initTestCounter);
		fflush(stdout);
	}

	initTestCounter++;
}

void PWM_startTesting(uint8_t Channel, uint8_t Duty, uint32_t Frequency, uint8_t ExpectedOutput)
{
	static int startTestCounter = 1;
	uint8_t output;

	output = Pwm_Start(Channel, Duty, Frequency);

	if(output == ExpectedOutput)
	{
		printf("PWM_start test %d Passed\n", startTestCounter);
		fflush(stdout);
	}else
	{
		printf("PWM_start test %d failed\n", startTestCounter);
		fflush(stdout);
	}

	startTestCounter++;
}

void PWM_updateTesting(uint8_t Channel, uint8_t Duty, uint32_t Frequency, uint8_t ExpectedOutput)
{
	static int updateTestCounter = 1;
	uint8_t output;

	output = Pwm_Update(Channel, Duty, Frequency);

	if(output == ExpectedOutput)
	{
		printf("PWM_update test %d Passed\n", updateTestCounter);
		fflush(stdout);
	}else
	{
		printf("PWM_update test %d failed\n", updateTestCounter);
		fflush(stdout);
	}

	updateTestCounter++;
}

void PWM_stopTesting(uint8_t Channel, uint8_t ExpectedOutput)
{
	static int stopTestCounter = 1;
	uint8_t output;

	output = Pwm_Stop(Channel);

	if(output == ExpectedOutput)
	{
		printf("PWM_stop test %d Passed\n", stopTestCounter);
		fflush(stdout);
	}else
	{
		printf("PWM_stop test %d failed\n", stopTestCounter);
		fflush(stdout);
	}

	stopTestCounter++;
}

int main(void)
{
	PWM_initTesting(0, E_NOK);
	PWM_initTesting(1, E_OK);
	PWM_initTesting(2, E_OK);
	PWM_initTesting(3, E_OK);
	PWM_initTesting(4, E_NOK);
	PWM_initTesting(5, E_NOK);

	printf("\n");

	PWM_startTesting(0, 0, 50, E_NOK);
	PWM_startTesting(2, 50, 500, E_OK);
	PWM_startTesting(3, 70, 5000, E_OK);
	PWM_startTesting(4, 70, 40000, E_NOK);
	PWM_startTesting(3, 100, 4, E_OK);
	PWM_startTesting(3, 120, 1000, E_NOK);
	PWM_startTesting(2, 70, 50000, E_NOK);

	printf("\n");

	PWM_updateTesting(0, 0, 50, E_NOK);
	PWM_updateTesting(2, 50, 500, E_OK);
	PWM_updateTesting(3, 70, 5000, E_OK);
	PWM_updateTesting(4, 70, 40000, E_NOK);
	PWM_updateTesting(3, 100, 4, E_OK);
	PWM_updateTesting(3, 120, 1000, E_NOK);
	PWM_updateTesting(2, 70, 50000, E_NOK);

	printf("\n");

	PWM_stopTesting(0, E_NOK);
	PWM_stopTesting(1, E_OK);
	PWM_stopTesting(2, E_OK);
	PWM_stopTesting(3, E_OK);
	PWM_stopTesting(4, E_NOK);


	return 0;
}
