
#ifndef I2C_LCFG
#define I2C_LCFG

#ifdef I2C_LCFG

/*Includes*/
#include "SERVICES/std_types.h"

/*Defines*/
#define I2C_MODULES_NUM (1u)

/*Macros*/
/*Defines*/

#define I2C_1 (0)
#define I2C_2 (1)
#define I2C_3 (2)

#define ACK_ENABLE (1)
#define ACK_DISABLE (0)

#define CK_STRETCH_EN (0)
#define CK_STRETCH_DIS (1)

#define PACKET_ERROR_EN (1)
#define PACKET_ERROR_DIS (0)

#define GEN_CALL_EN (1)
#define GEN_CALL_DIS (0)

#define POS_1ST_BYTE (0)
#define POS_NEXT_BYTE (1)

#define BUF_INT_EN (1)
#define BUF_INT_DIS (0)

#define ERR_INT_EN (1)
#define ERR_INT_DIS (0)

#define EVE_INT_EN (1)
#define EVE_INT_DIS (0)

#define FREQ_100K (1)

//#define SLAVE_ADDR ()

#define ADDRESS_MODE_7 (0)
#define ADDRESS_MODE_10 (1)

#define SLAVE_2ND_ADDR ()

#define DUAL_ADDR_EN (1)
#define DUAL_ADD_DIS (0)

#define I2C_SM (0)
#define I2C_FM (1)

#define DUTY_2 (0)
#define DUTY_16_9 (1)

#define FILTER_EN (1)
#define FILTER_DIS (0)

#define SLAVE_ADDR (0x50)

/*Check If Slave Addr Defined or not*/
#ifndef SLAVE_ADDR
#error Please Define Slave Addr
#endif

/*I2C Struct Declaration*/
typedef struct
{
	/*I2C Modue ID*/
	uint8_t I2C_ID;

	/*CR1 Configs*/
	uint8_t ACK_EN; //Acknowledge state
	uint8_t CK_Stretch;
	uint8_t PacketErr;
	uint8_t Gen_Call; //General Call enable
	uint8_t Pos;

	/*CR2 Configs*/
	uint8_t Err_IRQ_State; //disable or enable Error irq
	uint8_t Eve_IRQ_State; //disable or enable event irq

	/*OAR1 Configs*/
	uint8_t Addr_Mode:1; //10bit or 7bit
	uint16_t Dev_Address; // Configure Device Addr

	/*OAR2 Configs*/
	uint8_t Dual_Addr_State;
	uint8_t Add_2nd;

	/*CCR Configs*/
	uint8_t Mast_SpeedState : 1;
	uint8_t MastCK_Duty : 1;
	uint8_t Frequency;
	//uint16_t CCR_Val;//Define in mo3adla
//	uint8_t TRISE:5; FELMO3adla

	/*FLT Config*/
//	uint8_t Filter_Val; Mo3adla
	uint8_t Filter_CTRL:1;
}str_I2Ccfg_t;


extern str_I2Ccfg_t arr_I2C_Cfg[I2C_MODULES_NUM];

#endif
#endif
