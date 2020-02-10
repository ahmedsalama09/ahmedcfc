/*
 * uart.c
 *
 * Created: 10-Feb-20 2:21:06 PM
 *  Author: ahmed
 */ 
#include "uart.h"
#include "interrupt.h"
#include "registers.h"


/************************************************************************/
/*			Uart_init, takes a structure of inits                       */
/************************************************************************/
void uart_init(init_uart *uart){
	
	UCSRC = ((uart->parity) | (uart->stop) | (uart->uart_mode) | (uart->frame_size) | (uart->polarity) |(uart->synch));
	
	UBRRL = (uart->baud);
	UBRRH = (((uart->baud) >> 8) & 0x0F);
	
	UCSRB = ((uart->tx_rx_en) | (uart->tx_rx_irq));
}

/*send a byte to tx pin*/
void uart_tx_send(uint8_t data_send){
	
	while(!(UCSRA & UDRE_EMPTY));
	UDR = data_send;
}

/*Rec byte from uart receive*/
uint8_t uart_rx(void){
	
	if(UCSRB & RX_COMP_FLAG){
		return UDR;
	}
}

/*void set_callback(void (*local_ptr)(void))
{
	global_ptr = (volatile void(*)(void))local_ptr;
}

ISR(USART_RXC_irq){
	
	if(global_ptr != NULL){
		if(RX_COMP_FLAG & UCSRB){
			global_ptr();
		}	
	}
}*/
