/*
 * test.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Youssef Harby
 */


#include "DIO_TS/DIO.h"
#include <stdio.h>

DIO_Cfg_s cfg_test;

void DIO_initTesting(uint8_t gpio, uint8_t bit, uint8_t dir, uint8_t expected_output)
{
	static int initTestCounter = 1;
	uint8_t output;

	cfg_test.GPIO = gpio;
	cfg_test.pins = bit;
	cfg_test.dir = dir;

	output = DIO_init(&cfg_test);

	if(output == expected_output)
	{
		printf("DIO_init test %d Passed\n", initTestCounter);
		fflush(stdout);
	}else
	{
		printf("DIO_init test %d failed\n", initTestCounter);
		fflush(stdout);
	}

	initTestCounter++;
}

void DIO_writeTesting(uint8_t gpio, uint8_t bits, uint8_t value, uint8_t expected_output)
{
	static int writeTestCounter = 1;
	uint8_t output;

	output = DIO_Write(gpio, bits, value);

	if(output == expected_output)
	{
		printf("DIO_write test %d Passed\n", writeTestCounter);
		fflush(stdout);
	}else
	{
		printf("DIO_write test %d failed\n", writeTestCounter);
		fflush(stdout);
	}

	writeTestCounter++;
}

void DIO_readTesting(uint8_t gpio, uint8_t bits, uint8_t* value, uint8_t expected_output)
{
	static int readTestCounter = 1;
	uint8_t output;

	output = DIO_Read(gpio, bits, value);

	if(output == expected_output)
	{
		printf("DIO_read test %d Passed\n", readTestCounter);
		fflush(stdout);
	}else
	{
		printf("DIO_read test %d failed\n", readTestCounter);
		fflush(stdout);
	}

	readTestCounter++;
}

void DIO_toggleTesting(uint8_t gpio, uint8_t bits, uint8_t expected_output)
{
	static int toggleTestCounter = 1;
	uint8_t output;

	output = DIO_Toggle(gpio, bits);

	if(output == expected_output)
	{
		printf("DIO_toggle test %d Passed\n", toggleTestCounter);
		fflush(stdout);
	}else
	{
		printf("DIO_toggle test %d failed\n", toggleTestCounter);
		fflush(stdout);
	}

	toggleTestCounter++;
}

int main(void)
{
	uint8_t readVariable = 0;

	// DIO_init:
	// DIO_init test1:
	DIO_initTesting(0, 0, 0x00, E_OK);
	// DIO_init test2:
	DIO_initTesting(1, 9, 0xFF, E_OK);
	// DIO_init test3:
	DIO_initTesting(3, 17, 0xFF, E_OK);
	// DIO_init test4:
	DIO_initTesting(3, 9, 0x70, E_NOK);
	// DIO_init test5:
	DIO_initTesting(6, 0, INPUT, E_NOK);

	printf("\n");

	// DIO_write:
	// DIO_write test1:
	DIO_writeTesting(0, 0, 0x00, E_OK);
	// DIO_write test2:
	DIO_writeTesting(1, 9, 0xFF, E_OK);
	// DIO_write test3:
	DIO_writeTesting(3, 17, 0xFF, E_OK);
	// DIO_write test4:
	DIO_writeTesting(3, 5, 0x70, E_NOK);
	// DIO_write test5:
	DIO_writeTesting(6, 0, INPUT, E_NOK);

	printf("\n");

	// DIO_read:
	// DIO_read test1:
	DIO_readTesting(0, 0, NULL, E_NOK);
	// DIO_read test2:
	DIO_readTesting(1, 9, &readVariable, E_OK);
	// DIO_read test3:
	DIO_readTesting(3, 17, &readVariable, E_OK);
	// DIO_read test4:
	DIO_readTesting(3, 5, &readVariable, E_OK);
	// DIO_read test5:
	DIO_readTesting(6, 0, &readVariable, E_NOK);

	printf("\n");

	// DIO_toggle:
	// DIO_toggle test1:
	DIO_toggleTesting(0, 0, E_OK);
	// DIO_toggle test2:
	DIO_toggleTesting(1, 9, E_OK);
	// DIO_toggle test3:
	DIO_toggleTesting(3, 17, E_OK);
	// DIO_toggle test4:
	DIO_toggleTesting(6, 0, E_NOK);

	return 0;
}
