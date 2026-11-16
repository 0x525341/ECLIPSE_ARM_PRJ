#ifndef __SPI_H__
#define __SPI_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_spi.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_spi.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_spi.h"
#endif

#define SPI1_HANDLER		void SPI1_IRQHandler(void)
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#define SPI2_HANDLER		void SPI2_IRQHandler(void)
#if defined ( STM32F103xE )
#define SPI3_HANDLER		void SPI3_IRQHandler(void)
#endif
#endif

enum spi_num {
	SPI_1 = (uint32_t)SPI1,
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	SPI_2 = (uint32_t)SPI2,
#if defined ( STM32F103xE )
	SPI_3 = (uint32_t)SPI3
#endif
#endif
};

enum spi_mode {
	SPI_MODE_MASTER = LL_SPI_MODE_MASTER,
	SPI_MODE_SLAVE = LL_SPI_MODE_SLAVE
};

enum spi_length {
	SPI_LENGTH_8 = LL_SPI_DATAWIDTH_8BIT,
	SPI_LENGTH_16 = LL_SPI_DATAWIDTH_16BIT,
#if defined ( STM32F030x6 )
	SPI_LENGTH_4 = LL_SPI_DATAWIDTH_4BIT,
	SPI_LENGTH_5 = LL_SPI_DATAWIDTH_5BIT,
	SPI_LENGTH_6 = LL_SPI_DATAWIDTH_6BIT,
	SPI_LENGTH_7 = LL_SPI_DATAWIDTH_7BIT,
	SPI_LENGTH_9 = LL_SPI_DATAWIDTH_9BIT,
	SPI_LENGTH_10 = LL_SPI_DATAWIDTH_10BIT,
	SPI_LENGTH_11 = LL_SPI_DATAWIDTH_11BIT,
	SPI_LENGTH_12 = LL_SPI_DATAWIDTH_12BIT,
	SPI_LENGTH_13 = LL_SPI_DATAWIDTH_13BIT,
	SPI_LENGTH_14 = LL_SPI_DATAWIDTH_14BIT,
	SPI_LENGTH_15 = LL_SPI_DATAWIDTH_15BIT,
#endif
};


extern void spi_init(enum spi_num spi, uint32_t freq,
		enum spi_mode mode, uint32_t length, bool en_int);
extern void spi_start(enum spi_num spi);
extern void spi_stop(enum spi_num spi);
extern uint16_t spi_read(enum spi_num spi);
extern void spi_send(enum spi_num spi, uint16_t data);
extern bool spi_is_rcv_not_empty(enum spi_num spi);

#endif
