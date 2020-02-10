
#include "registers.h"
#include "SwICU.h"
#include "led.h"
#include "pushButton.h"
#include "timers.h"
#include "dcMotor.h"
#include "HwPWM.h"
#include "uart.h"
#include "ultrasonic.h"
#include "SPI.h"
#include "SPI_CONFIG.h"
#include "uart.h"
#include "uart_config.h"


int main(void)
{
	config_spi user_spi;
	init_uart user_uart;
	
	/************************************************************************/
	/*						SPI_INITS                                       */
	/************************************************************************/
	user_spi.bit_first = SPI_LSB_FIRST;
	user_spi.master_slave = MASTER_SELECT;
	user_spi.smp = R_SAMPLE_R_SETUP;
	user_spi.spi_en = SPI_EN;
	user_spi.spi_prescal = SPI_PRE_16;
	user_spi.spi_irq = SPI_INT_DIS;
	
	/************************************************************************/
	/*				UART_INITS					                            */
	/************************************************************************/
	user_uart.baud = BAUD_9600;
	user_uart.frame_size = DATA_8_BITS;
	user_uart.parity = PARITY_DISABLE;
	user_uart.polarity = POLARITY_0;
	user_uart.stop = ONE_STOP;
	user_uart.synch = ASYNCH;
	user_uart.tx_rx_en = (TX_ENABLE | RX_ENABLE);
	user_uart.tx_rx_irq = (TX_IRQ_DISABLE | RX_DISABLE);
	user_uart.uart_mode =UART_MODE;
	
	
	spi_init(&user_spi);
	uart_init(&user_uart);
	
	Led_Init(LED_0);
	while(1)
	{
		spi_tx('a');
		timer0DelayMs(1000);
	}
}