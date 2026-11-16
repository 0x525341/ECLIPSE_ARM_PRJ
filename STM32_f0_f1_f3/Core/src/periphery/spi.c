#include "spi.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_rcc.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_rcc.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_rcc.h"
#endif

/**
 * spi_init() - initialize SPI
 *
 * Return: none.
 */
void spi_init(enum spi_num spi, uint32_t freq,
		enum spi_mode mode, uint32_t length, bool en_int)
{
	LL_RCC_ClocksTypeDef rcc_clocks;
    LL_RCC_GetSystemClocksFreq(&rcc_clocks);

    LL_SPI_InitTypeDef SPI_InitStruct = {0};
	  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	  SPI_InitStruct.Mode = mode;
	  SPI_InitStruct.DataWidth = length;
	  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;

	  uint32_t div = 0;

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	  if(spi == SPI_2 || spi == SPI_3)
	  {
		  div = rcc_clocks.PCLK1_Frequency/freq;
	  }
	  else
	  {
		  div = rcc_clocks.PCLK2_Frequency/freq;
	  }
#elif defined ( STM32F030x6 )
	  div = rcc_clocks.PCLK1_Frequency/freq;
#endif

	  switch (div)
	  {
	  case 2:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;
		  break;
	  case 4:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV4;
		  break;
	  case 8:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8;
		  break;
	  case 16:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV16;
		  break;
	  case 32:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV32;
		  break;
	  case 64:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
		  break;
	  case 128:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV128;
		  break;
	  case 256:
		  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;
		  break;
	  default:
			//error
		  break;
	  }
	  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
	  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	  SPI_InitStruct.CRCPoly = 10;
	  LL_SPI_Init((SPI_TypeDef*)spi, &SPI_InitStruct);

#if defined ( STM32F030x6 )
	  LL_SPI_SetStandard((SPI_TypeDef*)spi, LL_SPI_PROTOCOL_MOTOROLA);
	  LL_SPI_EnableNSSPulseMgt((SPI_TypeDef*)spi);
#endif

		if (en_int)
		{
			LL_SPI_EnableIT_RXNE((SPI_TypeDef*)spi);
		}
}

void spi_start(enum spi_num spi)
{
	LL_SPI_Enable((SPI_TypeDef*)spi);
}

void spi_stop(enum spi_num spi)
{
	LL_SPI_Disable((SPI_TypeDef*)spi);
}

bool spi_is_rcv_not_empty(enum spi_num spi)
{
	if(LL_SPI_IsActiveFlag_RXNE((SPI_TypeDef*)spi) == SET)
		return true;
	return false;
}

uint16_t spi_read(enum spi_num spi)
{
	return LL_SPI_ReceiveData16((SPI_TypeDef*)spi);
}

void spi_send(enum spi_num spi, uint16_t data)
{
//	while(!LL_SPI_IsActiveFlag_BSY((SPI_TypeDef*)spi));
	LL_SPI_TransmitData16((SPI_TypeDef*)spi, data);
}
