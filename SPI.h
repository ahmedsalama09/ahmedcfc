/*
 * SPI.h
 *
 * Created: 10-Feb-20 6:04:17 PM
 *  Author: ahmed
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "std_types.h"
#include "SPI_CONFIG.h"
#include "registers.h"



void spi_init(config_spi *sp_inits);
void spi_tx(uint8_t send_spi);

#endif /* SPI_H_ */