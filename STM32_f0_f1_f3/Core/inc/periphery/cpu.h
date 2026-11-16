#ifndef __CPU_H__
#define __CPU_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F030x6 )
#include "stm32f0xx_ll_rcc.h"
#elif defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_rcc.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_rcc.h"
#endif
/* Defines */

/* Enumerations */
enum cpu_clk_src {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	CPU_CLK_HSI,
	CPU_CLK_HSE,
	CPU_CLK_LSI,
	CPU_CLK_LSE
#endif
};

#if defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum usart_clk_src {
#if defined ( STM32F030x6 )
	USART_CLK_PCLK1 = LL_RCC_USART1_CLKSOURCE_PCLK1,
	USART_CLK_SYSCLK = LL_RCC_USART1_CLKSOURCE_PCLK1,
#endif
#if defined ( STM32F373xC )
	USART_CLK_PCLK2 = LL_RCC_USART1_CLKSOURCE_PCLK2,
	USART_CLK_SYSCLK = LL_RCC_USART1_CLKSOURCE_SYSCLK,
#endif
	USART_CLK_LSE = LL_RCC_USART1_CLKSOURCE_LSE,
	USART_CLK_HSI = LL_RCC_USART1_CLKSOURCE_HSI,
};

enum I2C_clk_src {
	I2C_CLK_SYSCLK = LL_RCC_I2C1_CLKSOURCE_SYSCLK,
	I2C_CLK_HSI = LL_RCC_I2C1_CLKSOURCE_HSI,
};

enum RTC_clk_src {
	RTC_CLK_NONE = LL_RCC_RTC_CLKSOURCE_NONE,
	RTC_CLK_LSE = LL_RCC_RTC_CLKSOURCE_LSE,
	RTC_CLK_LSI = LL_RCC_RTC_CLKSOURCE_LSI,
	RTC_CLK_HSE_DIV32 = LL_RCC_RTC_CLKSOURCE_HSE_DIV32
};
#endif

enum cpu_clk_mul {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	CPU_CLK_MUL_NONE = -1,
	CPU_CLK_MUL_2 = LL_RCC_PLL_MUL_2,
	CPU_CLK_MUL_3 = LL_RCC_PLL_MUL_3,
	CPU_CLK_MUL_4 = LL_RCC_PLL_MUL_4,
	CPU_CLK_MUL_5 = LL_RCC_PLL_MUL_5,
	CPU_CLK_MUL_6 = LL_RCC_PLL_MUL_6,
	CPU_CLK_MUL_7 = LL_RCC_PLL_MUL_7,
	CPU_CLK_MUL_8 = LL_RCC_PLL_MUL_8,
	CPU_CLK_MUL_9 = LL_RCC_PLL_MUL_9,
	CPU_CLK_MUL_10 = LL_RCC_PLL_MUL_10,
	CPU_CLK_MUL_11 = LL_RCC_PLL_MUL_11,
	CPU_CLK_MUL_12 = LL_RCC_PLL_MUL_12,
	CPU_CLK_MUL_13 = LL_RCC_PLL_MUL_13,
	CPU_CLK_MUL_14 = LL_RCC_PLL_MUL_14,
	CPU_CLK_MUL_15 = LL_RCC_PLL_MUL_15,
	CPU_CLK_MUL_16 = LL_RCC_PLL_MUL_16
#endif
};

enum cpu_clk_div {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	CPU_CLK_DIV_1 = LL_RCC_SYSCLK_DIV_1,
	CPU_CLK_DIV_2 = LL_RCC_SYSCLK_DIV_2,
	CPU_CLK_DIV_4 = LL_RCC_SYSCLK_DIV_4,
	CPU_CLK_DIV_8 = LL_RCC_SYSCLK_DIV_8,
	CPU_CLK_DIV_16 = LL_RCC_SYSCLK_DIV_16,
	CPU_CLK_DIV_64 = LL_RCC_SYSCLK_DIV_64,
	CPU_CLK_DIV_128 = LL_RCC_SYSCLK_DIV_128,
	CPU_CLK_DIV_256 = LL_RCC_SYSCLK_DIV_256,
	CPU_CLK_DIV_512 = LL_RCC_SYSCLK_DIV_512
#endif
};

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum clk_APB1_div {
	APB1_DIV_1=LL_RCC_APB1_DIV_1,
	APB1_DIV_2=LL_RCC_APB1_DIV_2,
	APB1_DIV_4=LL_RCC_APB1_DIV_4,
	APB1_DIV_8=LL_RCC_APB1_DIV_8,
	APB1_DIV_16=LL_RCC_APB1_DIV_16,
};
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
enum clk_APB2_div {
	APB2_DIV_1=LL_RCC_APB2_DIV_1,
	APB2_DIV_2=LL_RCC_APB2_DIV_2,
	APB2_DIV_4=LL_RCC_APB2_DIV_4,
	APB2_DIV_8=LL_RCC_APB2_DIV_8,
	APB2_DIV_16=LL_RCC_APB2_DIV_16,
};
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
enum clk_adc_div {
	CLK_ADC_DIV_2 = LL_RCC_ADC_CLKSRC_PCLK2_DIV_2,
	CLK_ADC_DIV_4 = LL_RCC_ADC_CLKSRC_PCLK2_DIV_4,
	CLK_ADC_DIV_6 = LL_RCC_ADC_CLKSRC_PCLK2_DIV_6,
	CLK_ADC_DIV_8 = LL_RCC_ADC_CLKSRC_PCLK2_DIV_8,
};
#endif

/* Exported functions */
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
extern bool cpu_clk_init(uint32_t cpu_Hz, enum cpu_clk_src src, enum cpu_clk_mul mul, enum cpu_clk_div div, enum clk_APB1_div APB1_div, enum clk_APB2_div APB2_div, enum clk_adc_div ADC_div);
#elif defined ( STM32F030x6 )
extern bool cpu_clk_init(uint32_t cpu_Hz, enum cpu_clk_src src, enum cpu_clk_mul mul, enum cpu_clk_div div, enum clk_APB1_div APB1_div);
extern void adc_clk_14RC_init(void);
#endif

extern uint32_t cpu_get_clk(void);

#if defined ( STM32F030x6 ) || defined ( STM32F373xC )
extern void set_usart_clk_src(enum usart_clk_src src);
extern void set_I2C_clk_src(enum I2C_clk_src src);
extern void set_RTC_clk_src(enum RTC_clk_src src);
#endif

#endif
