/*
 * SPI_CONFOG.h
 *
 * Created: 10-Feb-20 10:10:56 PM
 *  Author: ahmed
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/*struct of all init configs*/
typedef struct spi_in{
	uint8_t spi_irq;
	uint8_t spi_en;
	uint8_t bit_first;
	uint8_t master_slave;
	uint8_t smp;
	uint8_t spi_prescal;
	}config_spi;

/************************************************************************/
/*			SPI REG_BITS_MACROS                                         */
/************************************************************************/
#define SPI_INT_EN		(0x80)
#define SPI_INT_DIS		(0x00)

#define SPI_EN			(0x40)
#define	SPI_DIS			(0x00)

#define MASTER_SELECT	(0x10)
#define SLAVE_SELECT	(0x00)

#define SPI_LSB_FIRST	(0x20)
#define SPI_MSB_FIRST	(0x00)

#define R_SAMPLE_R_SETUP	(0x00)
#define R_SETUP_R_SAMPLE	(0X04)
#define F_SAMPLE_F_SETUP	(0X08)
#define F_SETUP_F_SAMPLE	(0X0C)

#define SPI_PRE_4			(0X00)
#define SPI_PRE_16			(0X01)
#define	SPI_PRE_64			(0X02)
#define SPI_PRE_128			(0X03)

#define SPIF_FLAG			(0x80)
#define WCOL_FLAG			(0x40)

#define SPI_GPIO			(GPIOB)
#define MOSI				(BIT5)
#define MISO				(BIT6)
#define SCK					(BIT7)
#define SS					(BIT4)


#endif /* SPI_CONFOG_H_ */
