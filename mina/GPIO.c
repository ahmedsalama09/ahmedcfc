
#include "std_types.h"
#include "registers.h"
#include "gpio.h"

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction){
	
	/*use switch case to identify the port and initialize it
		u8_direction  0 ----> Init portA
		u8_direction  1 ----> Init portB
		u8_direction  2 ----> Init portC
		u8_direction  3 ----> Init portD*/
	switch(u8_port){
		case 0:
			PORTA_DIR = u8_direction;
			break;
			
		case 1:
			PORTB_DIR = u8_direction;
			break;
			
		case 2:
			PORTC_DIR = u8_direction;
			break;
			
		case 3: 
			PORTD_DIR = u8_direction;
			break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value){

	/*use switch case to identify the port and initialize it
		u8_direction  0 ----> Init portA
		u8_direction  1 ----> Init portB
		u8_direction  2 ----> Init portC
		u8_direction  3 ----> Init portD*/
	switch(u8_port){
		case 0:
		PORTA_DATA =u8_value;
		break;
		
		case 1:
		PORTB_DATA = u8_value;
		break;
		
		case 2:
		PORTC_DATA = u8_value;
		break;
		
		case 3:
		PORTD_DATA = u8_value;
		break;
	}

}

void gpioPortToggle(uint8_t u8_port){
	
	/*use switch case to identify the port and toggle it
		u8_direction  0 ----> Init portA
		u8_direction  1 ----> Init portB
		u8_direction  2 ----> Init portC
		u8_direction  3 ----> Init portD*/
	switch(u8_port){
		case 0:
		PORTA_DATA ^= 0xff;
		break;
		
		case 1:
		PORTB_DATA ^= 0xff;
		break;
		
		case 2:
		PORTC_DATA ^= 0xff;
		break;
		
		case 3:
		PORTD_DATA ^= 0xff;
		break;
	}
	
}

uint8_t gpioPortRead(uint8_t u8_port){
	
	/*a volatile variable to return the value*/
	uint8_t read_value;
	
	/*use switch case to identify the port and read it
		u8_direction  0 ----> Init portA
		u8_direction  1 ----> Init portB
		u8_direction  2 ----> Init portC
		u8_direction  3 ----> Init portD*/
	switch(u8_port){
		case GPIOA:
		read_value = PORTA_PIN;
		break;
		
		case GPIOB:
		read_value = PORTB_PIN;
		break;
		
		case GPIOC:
		read_value = PORTC_PIN;
		break;
		
		case GPIOD:
		read_value = PORTD_PIN;
		break;
	}
	return read_value;

}

void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction){
	
	if(u8_direction == ((uint8_t) 0xff)){
	
	/*use switch case to identify the port and initialize it
		u8_direction  0 ----> Init portA
		u8_direction  1 ----> Init portB
		u8_direction  2 ----> Init portC
		u8_direction  3 ----> Init portD*/
	switch(u8_port){
		case GPIOA:
			PORTA_DIR |= u8_pins;
			break;
			
		case GPIOB:
			PORTB_DIR |= u8_pins;
			break;
			
		case GPIOC:
			PORTC_DIR |= u8_pins;
			break;
			
		case GPIOD: 
			PORTD_DIR |= u8_pins;
			break;
	}
	}
	else if(u8_direction == ((uint8_t)0x00)){
		
		/*use switch case to identify the port and initialize it
		u8_direction  0 ----> Init portA
		u8_direction  1 ----> Init portB
		u8_direction  2 ----> Init portC
		u8_direction  3 ----> Init portD*/
	switch(u8_port){
		case GPIOA:
			PORTA_DIR &= ~u8_pins;
			break;
			
		case GPIOB:
			PORTB_DIR &= ~u8_pins;
			break;
			
		case GPIOC:
			PORTC_DIR &= ~u8_pins;
			break;
			
		case GPIOD: 
			PORTD_DIR &= ~u8_pins;
			break;
	}
	}
	
}

void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value){
	
	if(u8_value ==  HIGH){
		
		switch(u8_port){
					case GPIOA:
					PORTA_DATA |= u8_pins;
					break;
					
					case GPIOB:
					PORTB_DATA |=  u8_pins;
					break;
					
					case GPIOC:
					PORTC_DATA |=  u8_pins;
					break;
					
					case GPIOD:
					PORTD_DATA |=  u8_pins;
					break;
				}
		}
		else if(u8_value == LOW){
		
		switch(u8_port){
			case GPIOA:
			PORTA_DATA &= ~u8_pins;
			break;
			
			case GPIOB:
			PORTB_DATA &= ~u8_pins;
			break;
			
			case GPIOC:
			PORTC_DATA &= ~u8_pins;
			break;
			
			case GPIOD:
			PORTD_DATA &= ~u8_pins;
			break;
		}
		}
}

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins){
	
	switch(u8_port){
		case GPIOA:
		PORTA_DATA ^= u8_pins;
		break;
		
		case GPIOB:
		PORTB_DATA ^= u8_pins;
		break;
		
		case GPIOC:
		PORTC_DATA ^= u8_pins;
		break;
		
		case GPIOD:
		PORTD_DATA ^= u8_pins;
		break;
	}
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin){
	uint8_t returned_value;
	
	switch(u8_port){
		case GPIOA:
			returned_value = PORTA_PIN & u8_pin;
		break;
		
		case GPIOB:
			returned_value = PORTB_PIN & u8_pin;
		break;
		
		case GPIOC:
			returned_value = PORTC_PIN & u8_pin;
		break;
		
		case GPIOD:
			returned_value = PORTD_PIN & u8_pin;
		break;
	}
	if(returned_value == 0){
		return 0;
	}
	else
	return 1;
}