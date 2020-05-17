/*
 * I2C.c
 *
 *  Created on: May 16, 2020
 *      Author: ahmed
 */

#include "I2C.h"
#include "I2Clcg.h"
#include <MCAL/PerRegs.h>

/***********Macros***********/
/*Struct Macro*/
#define I2C_STRUCT arr_I2C_Cfg[au8_init_loop]

/*Init Macros*/
#define I2C_NOT_INIT (0)
#define I2C_INITIALIZED (1)

/*Clock Macros*/
#define I2C_1_CLOCK_EN (2097152u)

/*I2C Shifting define*/
#define I2C_ADDR_SHIFT (0x400u)

/*CR1 Macros*/
#define EN_PEC_SHIFT (5u)
#define EN_GENERALCALL_SHIFT (6u)
#define CLOCK_STRETCH_SHIFT (7u)
#define EN_ACK_SHIFT (10u)
#define POS_SHIFT (11u)
#define SWRST_SHIFT (15u)
#define PE_EN_SHIFT (0u)

#define START_GEN (1U)
#define START_SHIFT (8U)

#define SWRST_EN (1u)
#define PE_EN (1u)

/*CR2 Macros*/
#define FREQ_SHIFT (0u)
#define INT_ERR_SHIFT (8u)
#define INT_EVE_SHIFT (9u)

#define INT_BUF_MASK (0x0400u)

#define FREQ (4u)

/*OAR1 Macros*/
#define ADDR_MODE_SHIFT (15u)

#define ADDR_7BIT_SHIFT (1u)
#define ADDRESS_MASK (0x3FFu)

/*OAR2 Macros*/
#define DUAL_ADDR_SHIFT (1u)

/*CCR Macros*/
#define DUTY_SHIFT (14u)
#define FAST_STANDARD_SHIFT (15u)

#define CCR_MASK (0xFFFu)

#define MHZ_TO_100K (10u)
#define FREQ_SM_PSC (2u)
#define FREQ_FM_PSC_DUTY_ON (25u)
#define FREQ_FM_PSC_DUTY_OFF (3u)

/*SR1 Macros*/
#define TRANSMIT_EMPTY_MASK (0x0080u)

#define RECEIVE_EMPTY_MASK (0x0040u)

#define ACK_FAILURE (1U)
#define ACK_FAILURE_SHIFT (10U)

#define START_DETECT_MASK (0x0001U)

#define ADDRESS_MATCHED_MASK (0X0002U)

#define BUS_ERROR_MASK (0x0008u)

/*SR2 Macros*/
#define BUSY_MASK (0x0002U)

/*DR Macros*/
#define READ_BIT  (0x01u)
#define WRITE_BIT (0x00u)
#define ADDR_SHIFT (1u)


/************GLOBALS************/
/*Global Var To save init state*/
static uint8_t gu8_Init_state = I2C_NOT_INIT;
volatile static uint8_t gu8_Slave_Addr_IRQ = 0;
volatile static uint8_t *gPtrDataIRQ = 0;
volatile static uint16_t gu16_DataLengthIRQ = 0;

/*I2C Init
 * Description : Function to init I2C from an array of struct named
 * I2Clcfg.c "Linked"
 * Input : Void , Output : Void
 */
void I2C_Link_Init(void)
{
	if(gu8_Init_state == I2C_NOT_INIT)
	{
		uint8_t au8_init_loop = 0;

		/*Create Pointer To i2c Struct*/
		str_I2C_t *PtrI2C = (str_I2C_t *)I2C1_BASE;

		uint32_t I2C_BaseAddr= 0;

		for(au8_init_loop = 0 ; au8_init_loop < I2C_MODULES_NUM ; au8_init_loop++)
		{
			/*Config I2C Addr*/
			I2C_BaseAddr = (I2C1_BASE + (I2C_ADDR_SHIFT * I2C_STRUCT.I2C_ID));

			/*Init PTR Val*/
			PtrI2C = (str_I2C_t *)I2C_BaseAddr;

			/*init I2C_CLK*/
			RCC->APB1ENR |= (I2C_1_CLOCK_EN << I2C_STRUCT.I2C_ID);

			/*Packet Error Val*/
			PtrI2C->CR1 |= (I2C_STRUCT.PacketErr << EN_PEC_SHIFT);

			/*General Call*/
			PtrI2C->CR1 |= (I2C_STRUCT.Gen_Call << EN_GENERALCALL_SHIFT);

			/*Clock Stretch val*/
			PtrI2C->CR1 |= (I2C_STRUCT.CK_Stretch << CLOCK_STRETCH_SHIFT);

			/*ACK Val*/
			PtrI2C->CR1 |= (I2C_STRUCT.ACK_EN << EN_ACK_SHIFT);

			/*POS Val*/
			PtrI2C->CR1 |= (I2C_STRUCT.Pos << POS_SHIFT);

			/***************CR2 Configs**************/

			/*FreQ Val*/
			PtrI2C->CR2 |= (FREQ << FREQ_SHIFT);

			/*ERR Int*/
			PtrI2C->CR2 |= (I2C_STRUCT.Err_IRQ_State << INT_ERR_SHIFT);

			/*EvE Int*/
			PtrI2C->CR2 |= (I2C_STRUCT.Eve_IRQ_State << INT_EVE_SHIFT);

			/***************OAR1 Configs*************/

			/*Choose Addrs mode*/
			PtrI2C->OAR1 |= (I2C_STRUCT.Addr_Mode << ADDR_MODE_SHIFT);

			/*Write ADDR shifting is done to hanlde 7bits mode shift by one*/
			PtrI2C->OAR1 |= ((I2C_STRUCT.Dev_Address & ADDRESS_MASK) <<
							(ADDR_7BIT_SHIFT - I2C_STRUCT.Addr_Mode));

			/***************OAR2 Configs************/
			PtrI2C->OAR2 |= (I2C_STRUCT.Dual_Addr_State);
			PtrI2C->OAR2 |= (I2C_STRUCT.Add_2nd << DUAL_ADDR_SHIFT);

			/***************CCR Configs************/

			/*Check for mode*/
			if(I2C_STRUCT.Mast_SpeedState == I2C_SM)
			{
				PtrI2C->CCR |= (((FREQ * MHZ_TO_100K)/FREQ_SM_PSC) & CCR_MASK);
			}
			else if((I2C_STRUCT.Mast_SpeedState == I2C_FM) && (I2C_STRUCT.MastCK_Duty == DUTY_16_9))
			{
				PtrI2C->CCR |= (I2C_STRUCT.MastCK_Duty << DUTY_SHIFT);
				PtrI2C->CCR |= (((FREQ * MHZ_TO_100K) / FREQ_FM_PSC_DUTY_ON) & CCR_MASK);
			}
			else if((I2C_STRUCT.Mast_SpeedState == I2C_FM) && (I2C_STRUCT.MastCK_Duty == DUTY_2))
			{
				PtrI2C->CCR |= (((FREQ * MHZ_TO_100K) / FREQ_FM_PSC_DUTY_OFF) & CCR_MASK);
			}
			else
			{
				//path shouldn't go here so nothing done here
			}

			/***************TRISE CONFIG**********/
			PtrI2C->TRISE |= (FREQ + 1);

			/**************ENABLE PE AND ACK***********/
			PtrI2C->CR1 |= (PE_EN << PE_EN_SHIFT);

			PtrI2C->CR1 |= (I2C_STRUCT.ACK_EN << EN_ACK_SHIFT);

			gu8_Init_state = I2C_INITIALIZED;

		}
	}
	else
	{
		//Don't init as it was done before
	}
}

static void send_Data(uint8_t *PtrData, uint16_t DataLength , str_I2C_t *I2C)
{
	/*Create Loop Var*/
	uint16_t au16_loopVar = 0;

	for(au16_loopVar = 0; au16_loopVar < DataLength ; au16_loopVar++)
	{
		/*First check for buffer Empty*/
		while((I2C->SR1 & TRANSMIT_EMPTY_MASK ) != TRANSMIT_EMPTY_MASK);

		/*Send data thru DR*/
		I2C->DR = PtrData[au16_loopVar];
	}
}

static void Rec_Data(uint8_t *PtrData , uint16_t DataLength , str_I2C_t *I2C)
{
	/*Create loop Var*/
	uint16_t au16_loopVar = 0;

	for(au16_loopVar = 0; au16_loopVar < DataLength ; au16_loopVar++)
	{
		/*First Check for Received data*/
		while((I2C->SR1 & RECEIVE_EMPTY_MASK ) != RECEIVE_EMPTY_MASK);

		/*Receive Data From DR*/
		PtrData[au16_loopVar] = I2C->DR;
	}
}

ERROR_STATUS I2C_Master(uint8_t *PtrData , uint8_t SlaveADDR ,uint16_t DataLength
		, uint8_t I2C_ID , uint8_t Mast_State)
{
	/*First Create Error Var*/
	ERROR_STATUS ERR = E_NOK;

	/*Check if I2c Init or not*/
	if(gu8_Init_state == I2C_NOT_INIT)
	{
		ERR = ERROR_I2C_BASE + ERROR_MODULE_NOT_INIT;
	}
	else
	{
		/*Check for nullptr*/
		if(PtrData == NULL)
		{
			ERR  = ERROR_I2C_BASE + ERROR_NULL_PTR_INIT;
		}
		else
		{
			/*Create Ptr to i2c module*/
			str_I2C_t *I2C = (str_I2C_t *)(I2C1_BASE + (I2C_ID * I2C_ADDR_SHIFT));

			/*Check for no busy bus*/
			while((I2C->SR2 & BUSY_MASK) == BUSY_MASK);

			/*Send Start*/
			I2C->CR1 |= (START_GEN << START_SHIFT);

			/*Wait for start to be sent*/
			while((I2C->SR1 & START_DETECT_MASK) != START_DETECT_MASK);

			if(Mast_State == MASTER_SEND)
			{
				/*Send Slave Addr*/
				I2C->DR = (SlaveADDR << ADDR_SHIFT) + WRITE_BIT;

				/*Wait till slave ACK*/
				while((I2C->SR1 & ADDRESS_MATCHED_MASK) != ADDRESS_MATCHED_MASK);

				/*To clear Address REC Bit*/
				I2C->SR2;

				/*Send Data*/
				send_Data(PtrData , DataLength , I2C);
			}
			else if(Mast_State == MASTER_REC)
			{
				/*Send Slave Addr*/
				I2C->DR =(SlaveADDR << ADDR_SHIFT) + READ_BIT;

				/*Wait till slave ACK*/
				while((I2C->SR1 & ADDRESS_MATCHED_MASK) != ADDRESS_MATCHED_MASK);

				/*To clear Address REC Bit*/
				I2C->SR2;

				/*Rec Data*/
				Rec_Data(PtrData , DataLength , I2C);
			}

			else
			{
				ERR  = ERROR_I2C_BASE + ERROR_I2C_MASTER_FUNCTIONALITY;
			}
			ERR = E_OK;
		}
	}

	return ERR;
}

ERROR_STATUS I2C_Slave(uint8_t *PtrData, uint16_t DataLength, uint8_t I2C_ID, uint8_t Slave_State)
{
	/*Create Error Flag*/
	ERROR_STATUS ERR = E_NOK;

	if(gu8_Init_state == I2C_NOT_INIT)
	{
		ERR  = ERROR_I2C_BASE + ERROR_MODULE_NOT_INIT;
	}
	else
	{
		/*Check for null ptr*/
		if(PtrData == NULL)
		{
			ERR = ERROR_I2C_BASE + ERROR_NULL_PTR_INIT;
		}
		else
		{
			/*Create Ptr to i2c module*/
			str_I2C_t *I2C = (str_I2C_t *)(I2C1_BASE + (I2C_ID * I2C_ADDR_SHIFT));

			/*wait for address match*/
			while((I2C->SR1 & ADDRESS_MATCHED_MASK) != ADDRESS_MATCHED_MASK);

			/*Read sr2 to clr flag*/
			I2C->SR2;

			/*Check for slave functionality*/
			if(Slave_State == SLAVE_SEND)
			{
				send_Data(PtrData , DataLength , I2C);
			}
			else if(Slave_State == SLAVE_REC)
			{
				Rec_Data(PtrData , DataLength , I2C);
			}
			else
			{
				ERR = ERROR_I2C_BASE + ERROR_I2C_MASTER_FUNCTIONALITY;
			}

			ERR = E_OK;
		}
	}
	return ERR;
}

ERROR_STATUS I2C_Master_IRQ(uint8_t *PtrData , uint8_t SlaveADDR ,uint16_t DataLength
		, uint8_t I2C_ID , uint8_t Mast_State)
{
	/*First Create Error Var*/
	ERROR_STATUS ERR = E_NOK;

	/*Check if I2c Init or not*/
	if(gu8_Init_state == I2C_NOT_INIT)
	{
		ERR = ERROR_I2C_BASE + ERROR_MODULE_NOT_INIT;
	}
	else
	{
		/*Check for nullptr*/
		if(PtrData == NULL)
		{
			ERR  = ERROR_I2C_BASE + ERROR_NULL_PTR_INIT;
		}
		else
		{
			/*Create Ptr to i2c module*/
			str_I2C_t *I2C = (str_I2C_t *)(I2C1_BASE + (I2C_ID * I2C_ADDR_SHIFT));

			/*Save length of data and address to be used in irq*/
			gPtrDataIRQ = PtrData;
			gu16_DataLengthIRQ = DataLength;

			/*Check For busy state of bus*/
			if((I2C->SR2) & BUSY_MASK)
			{
				ERR = ERROR_I2C_BASE + ERROR_BUS_BUSY;
			}
			else
			{
				/*Check for read or write operation*/
				if(Mast_State == MASTER_SEND)
				{
					/*Save Slave Address + Read or write bit in global Var*/
					gu8_Slave_Addr_IRQ = (SlaveADDR + WRITE_BIT);

					ERR = E_OK;
				}
				else if(Mast_State == MASTER_REC)
				{
					gu8_Slave_Addr_IRQ = (SlaveADDR + READ_BIT);

					ERR = E_OK;
				}
				else
				{
					/*Save error wrong function*/
					ERR = ERROR_I2C_BASE + ERROR_I2C_MASTER_FUNCTIONALITY;
				}

				if(ERR == E_OK)
				{
					/*Send start*/
					I2C1->CR1 |= (START_GEN << START_SHIFT);
				}
			}
		}

	}

	return ERR;
}

void I2C1_EV_IRQHandler(void)
{
	/*Create local loop variable*/
	static uint16_t au16_loop = 0;

	/*Check for start Bit*/
	if((I2C1->SR1 & START_DETECT_MASK) == START_DETECT_MASK)
	{
		/*Send Slave ADDR*/
		I2C1->DR = gu8_Slave_Addr_IRQ;
	}

	else if((I2C1->SR1 & ADDRESS_MATCHED_MASK) == ADDRESS_MATCHED_MASK)
	{
		/*Read SR2 To clr Flag*/
		I2C1->SR2;

		/*Enable Buf IRQ*/
		I2C1->CR2 |= INT_BUF_MASK;
	}
	else if((I2C1->SR1 & TRANSMIT_EMPTY_MASK) == TRANSMIT_EMPTY_MASK)
	{
		/*Send data byte by byte*/
		if(au16_loop < gu16_DataLengthIRQ)
		{
			I2C1->DR = gPtrDataIRQ[au16_loop];

			au16_loop++;
		}
		else
		{
			/*Disable buf irq and reset cnt*/
			au16_loop =0;

			/*Disable Buf INT*/
			I2C1->CR2 &= ~INT_BUF_MASK;
		}
	}
	else if((I2C1->SR1 & TRANSMIT_EMPTY_MASK) == TRANSMIT_EMPTY_MASK)
		{
		/*Send data byte by byte*/
				if(au16_loop < gu16_DataLengthIRQ)
				{
					 gPtrDataIRQ[au16_loop] =I2C1->DR ;

					au16_loop++;
				}
				else
				{
					/*Disable buf irq and reset cnt*/
					au16_loop =0;

					/*Disable Buf INT*/
					I2C1->CR2 &= ~INT_BUF_MASK;
				}
		}
}
