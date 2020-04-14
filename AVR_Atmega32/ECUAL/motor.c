/*
 * motor.c
 *
 * Created: 18-Feb-20 8:03:05 PM
 *  Author: ahmed
 */ 
#include "motor.h"
#include "/Sprint projects/SOS&CarApp/Car by sos/MCAL/DIO.h"
#include "/Sprint projects/SOS&CarApp/Car by sos/MCAL/PWM.h"	


/************************************************************************/
/*						DEFINES                                         */
/************************************************************************/
#define MOTOR_FREQUENCY (50)


/************************************************************************/
/*					APIS                                                */
/************************************************************************/
/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS Motor_Init(uint8_t Motor_Number){
	 
	 /*create error flag*/
	 ERROR_STATUS error_flag = E_OK;
	 
	 
	 /*create dio data structure*/
	 st_DIO_Cfg_t st_MotorDio;
	 Pwm_Cfg_s st_PwmMotor_t;
	 
	 switch(Motor_Number){
		case MOTOR_1: 
				/*set EN1, Forward PD4 , Backward PD3*/
				st_MotorDio.dir = OUTPUT;
				st_MotorDio.pins = (PIN4 | PIN2 | PIN3);
				st_MotorDio.GPIO = GPIOD;
				
				/*read error status and init io pins of motor*/
				error_flag |= DIO_init(&st_MotorDio);
				
				 /*create PWM struct for CH1A*/
				 st_PwmMotor_t.Channel = PWM_CH1A;
				 st_PwmMotor_t.Prescaler = PWM_PRESCALER_64;
				  
				  /*init pwm..CH1A and read error status*/
				 error_flag |= Pwm_Init(&st_PwmMotor_t);
				
		break;
		
		case MOTOR_2:
			
			/*set EN1,Forward PD6,Backward PD7*/
			st_MotorDio.dir = OUTPUT;
			st_MotorDio.pins = (PIN5 | PIN6 | PIN7);
			st_MotorDio.GPIO = GPIOD;
			
			/*init DIO pins and read the error status*/
			error_flag |= DIO_init(&st_MotorDio);
		
			/*init PWM for CH1B*/
			st_PwmMotor_t.Channel = PWM_CH1B;
			st_PwmMotor_t.Prescaler = PWM_PRESCALER_64;
			
			/*init pwm..CH1A*/
			error_flag |= Pwm_Init(&st_PwmMotor_t);
		break;
	 }
	return error_flag;	 
 }
 
 /**
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backword
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor direction from getting the motor number and the direction.
*/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*check which motor to work at*/
	switch(Motor_Number){
		
		case MOTOR_1:
		
			/*check it's direction*/
			switch(Motor_Direction){
				
				case MOTOR_FORWARD:
					
					/*set en,forward direction*/
					DIO_Write(GPIOD,PIN4,HIGH);
					DIO_Write(GPIOD,PIN2,HIGH);
					DIO_Write(GPIOD,PIN3,LOW);
					
				break;
				
				case MOTOR_BACKWARD:
					
					/*set en,backward direction*/
					DIO_Write(GPIOD,PIN4,HIGH);
					DIO_Write(GPIOD,PIN3,HIGH);
					DIO_Write(GPIOD,PIN2,LOW);
					
				break;
			}
			break;
			
		case MOTOR_2:
			switch(Motor_Direction){
				case MOTOR_FORWARD:
				
					/*set en,forward direction*/
					DIO_Write(GPIOD,PIN5,HIGH);
					DIO_Write(GPIOD,PIN6,HIGH);
					DIO_Write(GPIOD,PIN7,LOW);
				
				break;
			
				case MOTOR_BACKWARD:
				
					/*set en,backward direction*/
					DIO_Write(GPIOD,PIN5,HIGH);
					DIO_Write(GPIOD,PIN7,HIGH);
					DIO_Write(GPIOD,PIN6,LOW);
				break;
				
				default:
					/*not configured direction*/
					error_flag = E_NOK;
			}
		default:
			
			/*not found motor*/
			error_flag = E_NOK;
	}
	return error_flag;
}

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*switch motor*/
	switch(Motor_Number){
		
		case MOTOR_1:
			
			/*set motor speed by starting PWM1A*/
			error_flag |= Pwm_Start(PWM_CH1A,Mot_Speed,MOTOR_FREQUENCY);
			
		break;
		
		case MOTOR_2:
		
			/*set motor speed by starting PWM1B*/
			error_flag |= Pwm_Start(PWM_CH1B,Mot_Speed,MOTOR_FREQUENCY);
				
		break;
			
		default:
		
			/*wrong motor number entered*/
			error_flag = E_NOK;
		break;
	}
	
	/*return OK*/
	return error_flag;
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*switch motor*/
	switch(Motor_Number){
		
		case MOTOR_1:
		
			/*set motor speed by starting PWM1A*/
			error_flag |= Pwm_Start(PWM_CH1A,Speed,MOTOR_FREQUENCY);
		
		break;
		
		case MOTOR_2:
		
			/*set motor speed by starting PWM1B*/
			error_flag |= Pwm_Start(PWM_CH1B,Speed,MOTOR_FREQUENCY);
		
		break;
		
		default:
		
			/*wrong motor number entered*/
			error_flag = E_NOK;
		break;
	}
	
		/*return OK*/
		return error_flag;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: stop the motor.
*/

ERROR_STATUS Motor_Stop(uint8_t Motor_Number){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*check for channels*/
	switch(Motor_Number){
		
		case MOTOR_1:
		
			/*for channel 1 disable EN1 by writing low to PD4*/
			error_flag |= Pwm_Stop(PWM_CH1A);
			
		break;
			
		case MOTOR_2:
			
			/*disable EN2 by writing low to PD5*/
			error_flag |= Pwm_Stop(PWM_CH1B);
			
		break;
		
		default:
			
			/*wrong motor entered then it's not okay*/
			error_flag = E_NOK;
		break;
	}
	
	/*return error status*/
	return error_flag;	
}