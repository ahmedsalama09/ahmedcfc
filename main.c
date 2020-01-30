
#include "registers.h"
#include "SwICU.h"
#include "led.h"
#include "pushButton.h"
#include "dcMotor.h"
#include "HwPWM.h"

#define moto_freq 100000

int main(void)
{
	uint8_t u8_swIcuDistance = 0;
	uint8_t u8_dutyCycle = 8;
	uint8_t u8_obstacle;
	
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);
	
	SwICU_Init(SwICU_EdgeRisiging);


	HwPWMInit();
	HwPWMSetDuty(u8_dutyCycle, moto_freq);

	while(1)
	{
		timer2DelayMs(300);
		/*read the obstacle measures*/
		u8_obstacle = ultrasonic_read();
		
		if(u8_obstacle > 5){
			MotorDC_Dir(MOT_1, STOP);
			MotorDC_Dir(MOT_2, STOP);
		}else
		{
			MotorDC_Dir(MOT_1, FORWARD);
			MotorDC_Dir(MOT_2, FORWARD);
		}
	}
}