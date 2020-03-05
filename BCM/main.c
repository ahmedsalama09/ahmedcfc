/*
 * Basic_Comm_Module.c
 *
 * Created: 2020-03-01 9:49:13 PM
 * Author : AHMED_SALAMA
 */ 

#include "bcm.h"
#include "registers.h"
#include "interrupt.h"
#include "uart.h"

#define RECEIVE


#ifdef SEND
/**First half of the project
	*Description : sending from pc to uart then from spi->spi
	**receiving data till '@' is received then we send that buffer to the other spi side
	*please define it to use it*/
	
	
volatile void fun1(){
	
}
uint8_t arr[20];
int main(void)
{
	uint8_t cnt=0;
	uart_init(&st_uart_init);
	
	while(1)
	{
		arr[cnt] = uart_rx();
		
		if(arr[cnt] == '@')
		{
				break;
		}
		cnt++;
	}
	BCM_Cfg.Transmit_Cbk = fun1;
	
	BCM_Init(&BCM_Cfg);

	sei();
	BCM_Send(arr,cnt);

    while (1) 
    {
		BCM_TxDispatcher();

    }
}

/*Other side of project
*Description : here is the receiving spi side then sending data back to pc
**the data is sent at BCM after receiving it so please check it
***please make sure that spi is configure as a slave

*/

#else 

#define BUFFER_SIZE		(20)

uint8_t arr[20];

volatile void fun1(uint16_t uart_size){
	
	uint16_t u16_loop = ZERO;
	
	for(u16_loop = 0; u16_loop <= uart_size ; u16_loop++)
	{
		uart_tx_send('a');
	}
}



int main(void)
{

	uart_init(&st_uart_init);
	
	BCM_Cfg.Recieve_Cbk = fun1;
	
	BCM_Init(&BCM_Cfg);

	sei();
	BCM_SetupReceive(arr,BUFFER_SIZE);

	while (1)
	{
		BCM_RxDispatcher();

	}
}
#endif