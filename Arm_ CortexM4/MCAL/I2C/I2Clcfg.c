

/*Includes */
#include "I2Clcg.h"



/*Create Array Of structs*/
str_I2Ccfg_t arr_I2C_Cfg[I2C_MODULES_NUM] = {{.I2C_ID = I2C_1 ,
											.ACK_EN = ACK_ENABLE ,
											.Frequency = FREQ_100K ,
											.Gen_Call = GEN_CALL_DIS ,
											.CK_Stretch = CK_STRETCH_EN ,
											.PacketErr = PACKET_ERROR_EN ,
											.Pos = POS_1ST_BYTE ,
											.Err_IRQ_State = ERR_INT_EN ,
											.Eve_IRQ_State = EVE_INT_EN,
											.Addr_Mode = ADDRESS_MODE_7 ,
										#ifdef SLAVE_ADDR
											.Dev_Address = SLAVE_ADDR ,
										#endif
											.Dual_Addr_State = DUAL_ADD_DIS ,
											.Mast_SpeedState =I2C_SM ,
											.MastCK_Duty = DUTY_2,
											.Filter_CTRL = FILTER_EN
											},
};
