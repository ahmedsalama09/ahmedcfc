
#include "registers.h"
#include "SwICU.h"
#include "led.h"
#include "pushButton.h"
#include "timers.h"
#include "dcMotor.h"
#include "HwPWM.h"
#include "ultrasonic.h"

#define moto_freq 100000
uint16_t u8_obstacle;
int main(void)
{
	uint8_t u8_dutyCycle = 8;
	
	
	//MotorDC_Init(MOT_1);
	//MotorDC_Init(MOT_2);
//	MotorDC_Dir(MOT_1, FORWARD);
	//MotorDC_Dir(MOT_2, FORWARD);
	
//	SwICU_Init(SwICU_EdgeRisiging);

	ultasonic_init();
	//HwPWMInit();
	//HwPWMSetDuty(u8_dutyCycle, moto_freq);
	Led_Init(LED_1);
	wave_send();
	while(1)
	{
		
		/*read the obstacle measures*/
		u8_obstacle = ultrasonic_read();
		
		if(u8_obstacle > 5){
			//MotorDC_Dir(MOT_1, STOP);
			//MotorDC_Dir(MOT_2, STOP);
			//Led_Off(LED_1);
		}else
		{
			//MotorDC_Dir(MOT_1, FORWARD);
			//MotorDC_Dir(MOT_2, FORWARD);
		//	Led_On(LED_1);
		}
	}
}