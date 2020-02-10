/*
 * uart_config.h
 *
 * Created: 10-Feb-20 10:46:38 PM
 *  Author: ahmed
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

typedef struct init_uart{
	
	uint8_t parity;
	uint8_t frame_size;
	uint8_t stop;
	uint8_t polarity;
	uint8_t synch;
	uint8_t tx_rx_en;
	uint16_t baud;
	uint8_t uart_mode;
	uint8_t tx_rx_irq;
	}init_uart;

/*bits locations*/
#define ASYNCH				(0x00)
#define SYNCH				(0x40)

#define RX_ENABLE			(0X10)
#define RX_DISABLE			(0X00)
#define RX_INT_ENABLE		(0X80)
#define RX_INT_DISABLE		(0X80)

#define TX_ENABLE			(0X08)
#define TX_DISABLE			(0X00)
#define TX_IRQ_EN			(0X40)
#define TX_IRQ_DISABLE		(0X00)

#define UDRE_INT_ENABLE		(0X20)

#define UART_MODE			(0X00)
#define USART_MODE			(0X40)

#define PARITY_DISABLE		(0X00)
#define EVEN_PARITY			(0X20)
#define ODD_PARITY			(0X30)

#define ONE_STOP			(0X00)
#define TWO_STOPS			(0X80)

#define DATA_5_BITS			(0X00)
#define DATA_6_BITS			(0X02)
#define DATA_7_BITS			(0X04)
#define DATA_8_BITS			(0X06)

#define POLARITY_0			(0x00)

#define BAUD_4800			(206)
#define BAUD_9600			(103)

#define UDRE_EMPTY			(0x20)

#define RX_COMP_FLAG		(0x80)


#endif /* UART_CONFIG_H_ */
