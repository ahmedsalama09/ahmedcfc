/*
 * uart.h
 *
 * Created: 10-Feb-20 1:12:29 PM
 *  Author: ahmed
 */ 


#ifndef UART_H_
#define UART_H_
#include "std_types.h"
#include "uart_config.h"

/************************************************************************/
/*			Uart_init, takes a structure of inits                       */
/************************************************************************/
void uart_init(init_uart *uart);

/*send a byte to tx pin*/
void uart_tx_send(uint8_t data_send);


//void set_callback(void (*local_ptr)(void));
/*Rec byte from uart receive*/
uint8_t uart_rx(void);

#endif /* UART_H_ */