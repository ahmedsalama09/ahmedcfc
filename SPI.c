/*
 * SPI.c
 *
 * Created: 10-Feb-20 6:11:46 PM
 *  Author: ahmed
 */
#include "SPI.h"
#include "gpio.h"
#include "SPI_CONFIG.h"

void spi_init(config_spi *sp_inits){//uint8_t spi_irq,uint8_t spi_en,uint8_t bit_first,uint8_t master_slave,uint8_t smp,uint8_t spi_prescal){
	
	SPCR = ((sp_inits->spi_irq) | (sp_inits->spi_en) | (sp_inits->bit_first) | (sp_inits->smp) | (sp_inits->spi_prescal) | (sp_inits->master_slave));
	
	if((sp_inits->master_slave) == MASTER_SELECT){
		
		/*set MOSI as OUT*/
		gpioPinDirection(SPI_GPIO,MOSI,HIGH);
		gpioPinDirection(SPI_GPIO,MISO,LOW);
		
		/*set ck as out*/
		gpioPinDirection(SPI_GPIO,BIT7,HIGH);
	}
	else if((sp_inits->master_slave) == SLAVE_SELECT){
		
		/*set MOSI as IN*/
		gpioPinDirection(SPI_GPIO,MOSI,LOW);
		gpioPinDirection(SPI_GPIO,MISO,HIGH);
		
		/*set ck as in*/
		gpioPinDirection(SPI_GPIO,SCK,LOW);
	}
}

void spi_tx(uint8_t send_spi){
	
	/*wait for spif_flag to be HIGH*/
	while(!((SPSR & SPIF_FLAG)))
	/*send data*/
	SPDR = send_spi;
	
}