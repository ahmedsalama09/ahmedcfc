/*
 * I2C.h
 *
 *  Created on: May 16, 2020
 *      Author: ahmed
 */

#ifndef MCAL_I2C_H_
#define MCAL_I2C_H_

#include <SERVICES/Error_table.h>
#include <SERVICES/std_types.h>

/*User Macros*/
#define _I2C_1 (0U)
#define _I2C_2 (1U)
#define _I2C_3 (2U)

#define MASTER_SEND (0U)
#define MASTER_REC (1U)

#define SLAVE_SEND (0U)
#define SLAVE_REC (1U)

void I2C_Link_Init(void);

ERROR_STATUS I2C_Master(uint8_t *PtrData , uint8_t SlaveADDR ,uint16_t DataLength
		, uint8_t I2C_ID , uint8_t Mast_State);

ERROR_STATUS I2C_Slave(uint8_t *PtrData, uint16_t DataLength, uint8_t I2C_ID, uint8_t Slave_State);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);

#endif /* MCAL_I2C_H_ */
