/*
 * DIO.c
 *
 * Created: 16-Feb-20 9:49:54 PM
 *  Author: ahmed
 */

/************************************************************************/
/*						INCLUDES                                        */
/************************************************************************/
#include "DIO.h"
#include "/carApp/carApp/carApp/SERVICES/std_types.h" 
 
 
 /************************************************************************/
 /*						APIS                                             */
 /************************************************************************/
 /*
 *Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
 *Output: No output
 *In/Out:
 *Description: This function can set the direction of a full port, a nibble
 * 			  or even one pin.
 */
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
	
	/*create error FLAG*/
	ERROR_STATUS error_flag = E_OK;
	
	/*check if the pointer doesn't point to anything*/
	if(DIO_info == NULL){
		
		/*return FAILED*/
		error_flag = E_NOK;
	}
	
	/*switch ports*/
	switch(DIO_info->GPIO){
		
		case GPIOA:
		
		   /*check the direction then write it*/
		   if(DIO_info->dir == INPUT){
			   
			   /*clear the desired pins*/
			   PORTA_DIR &= ~(DIO_info->pins);
		   }
		   
		   else if(DIO_info->dir == OUTPUT){
			   
			   /*set the desired pins*/
			   PORTA_DIR |= (DIO_info->pins);
		   }
		   
		   else{
			   /*wrong mode chosen*/
			   error_flag = E_NOK;
		   }
		   
		break;
		   
		case GPIOB:
		   
		   /*check the direction then write it*/
		   if(DIO_info->dir == INPUT){
			   
			   /*clear the chosen pins*/
			   PORTB_DIR &= ~(DIO_info->pins);
		   }
		   
		   else if(DIO_info->dir == OUTPUT){
			   
			   /*set the chosen pins*/
			   PORTB_DIR |= (DIO_info->pins);
		   }
		   
		   else{
			   /*wrong mode chosen*/
			   error_flag = E_NOK;
		   }
		   
		break;
		   
		case GPIOC:
		   
		   /*check the direction then write it*/
		   if(DIO_info->dir == INPUT){
			   
			   /*clear the chosen pins*/
			   PORTC_DIR &= ~(DIO_info->pins);
		   }
		   
		   else if(DIO_info->dir == OUTPUT){
			   
			   /*set the chosen pins*/
			   PORTC_DIR |= (DIO_info->pins);
		   }
		   
		   else{
			   /*wrong mode chosen*/
			   error_flag = E_NOK;
		   }
		   
		break;
		   
		case GPIOD:
		   
		   /*check the direction then write it*/
		   if(DIO_info->dir == INPUT){
			   
			   /*clear the chosen pins*/
			   PORTD_DIR &= ~(DIO_info->pins);
		   }
		   else if(DIO_info->dir == OUTPUT){
			   
			   /*set the chosen pins*/
			   PORTD_DIR |= (DIO_info->pins);
		   }
		   
		   else{
			   /*wrong mode chosen*/
			   error_flag = E_NOK;
		   }
		   
		break;
		
		/*wrong GPIO entered then it's not ok*/
		default:
		   
		   error_flag = E_NOK;
		break;
	}
	
	/*return OK*/
	return error_flag;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*check the entered channel*/
	switch(GPIO){
		
		/*check if it's GPIOA*/
		case GPIOA:
		   
		   /*set the pins at PORTA DATA REG*/
		   if(value == HIGH){
			   
			   /*set the pin at PORT DATA REG*/
			   PORTA_DATA = (pins);
		   }
		   
		   /*if low then reset it*/
		   else if(value == LOW){
			   
			   /*reset the pin at port data reg*/
			   PORTA_DATA &= ~(pins);
		   }
		   
		   else{
				/*wrong mode chosen*/
				   error_flag = E_NOK;
		   }
		   
		break;
		
		/*check if it's GPIOB*/
		case GPIOB:
		
		   /*set the pins at PORTB DATA REG*/
		   if(value == HIGH){
			
			   /*set the pin at PORT DATA REG*/
			   PORTB_DATA = (pins);
		   }
		
		   /*if low then reset it*/
		   else if(value == LOW){
			
			   /*reset the pin at port data reg*/
			   PORTB_DATA &= ~(pins);
		   }
		
		   else{
			   /*wrong mode chosen*/
			   error_flag = E_NOK;
		   }
		
		break;
		
		/*check if it's GPIOC*/
		case GPIOC:
		
		   /*set the pins at PORTC DATA REG*/
		   if(value == HIGH){
			
			   /*set the pin at PORT DATA REG*/
			   PORTC_DATA = (pins);
		   }
		
		   /*if low then reset it*/
		   else if(value == LOW){
			
			   /*reset the pin at port data reg*/
			   PORTC_DATA &= ~(pins);
		   }
		
		   else{
			   /*wrong mode chosen*/
			   error_flag = E_NOK;
		   }
		
		   break;
		 
		 /*check if GPIOD*/  
		 case GPIOD:
		   		
		   	/*set the pins at PORTD DATA REG*/
		   	if(value == HIGH){
			   		
			   	/*set the pin at PORT DATA REG*/
			   	PORTD_DATA = (pins);
		   	}
		   		
		   	/*if low then reset it*/
		   	else if(value == LOW){
			   		
			   	/*reset the pin at port data reg*/
			   	PORTD_DATA &= ~(pins);
		   	}
		   		
		   	else{
				   
			   	/*wrong mode chosen*/
			   	error_flag = E_NOK;
		   	}
		   		
		 break;
		 
		 default:
		    
			/*wrong gpio chosen then return not ok*/
			error_flag = E_NOK;
		 break;
	}
	
	
	/*things worked fine then return E_OK*/
	return error_flag;
} 

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*if data pointer pointing to nothing then it's not ok*/
	if(data == NULL){
		
		return E_NOK;
	}
	
	/*check which gpio you working on then configure it*/
	switch(GPIO){
		
		/*first case is GPIOA*/
		case GPIOA:
		   
		   /*return desired values*/
		   *data = (PORTA_PIN & pins);
		break;
		
		/*second case is GPIOB*/
		case GPIOB:
				
			/*return desired values*/
			*data = (PORTB_PIN & pins);
		break;
			
		/*3rd case is GPIOC*/
		case GPIOC:
			
			/*return desired values*/
			*data = (PORTC_PIN & pins);
		break;
		
		/*4th case is GPIOD*/
		case GPIOD:
		
		   /*return desired values*/
		   *data = (PORTB_PIN & pins);
		   
		break;
		   
		/*wrong port is chosen then return not ok*/   
		default:
		   
		   error_flag = E_NOK;
		break;
	}
	
	/*things worked fine then return E_OK*/
	return error_flag;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins){
	
	/*create error flag*/
	ERROR_STATUS error_flag = E_OK;
	
	/*check for the GPIO*/
	switch(GPIO){
		
		case GPIOA:
		
			/*toggle the selected pins of port a */
			PORTA_DATA ^= pins;
			
		break;
		
		case GPIOB:
		
			/*toggle the selected pins of port b*/
			PORTB_DATA ^= pins;
			
		break;
		
		case GPIOC:
		
			/*toggle the selected pins of port c*/
			PORTC_DATA ^= pins;
			
		break;
		
		case GPIOD:
		
			/*toggle the selected pin of port d*/
			PORTD_DATA ^= pins;
			
		break;
		
		default:
			
			/*wrong port entered then return not ok*/
			error_flag = E_NOK;	
	}
	
	/*return OK as it worked fine by reaching that point*/
	return error_flag;
}