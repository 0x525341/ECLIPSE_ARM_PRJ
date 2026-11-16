#include "cpu.h"
#include "clk.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "system_stm32f1xx.h"
#include "stm32f1xx_ll_system.h"
#elif defined ( STM32F030x6 )
#include "system_stm32f0xx.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#elif defined ( STM32F373xC )
#include "system_stm32f3xx.h"
#include "stm32f3xx_ll_system.h"
#endif

static uint32_t get_clock(void) {
	SystemCoreClockUpdate();
	return SystemCoreClock;
}

static void set_flash_latency(uint32_t clock) {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	uint32_t latency = 0;
	if (clock <= 25000000) {
		LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
		latency = LL_FLASH_LATENCY_0;
	} else if (clock <= 50000000) {
		LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
		latency = LL_FLASH_LATENCY_1;
	}
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	else if (clock<=75000000)
	{
		LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
		latency = LL_FLASH_LATENCY_2;
	}
#endif

	while (LL_FLASH_GetLatency() != latency) {

	}

#endif
}

/**
 * cpu_init() - set clock of cpu
 * @src:	Source for cpu clock.
 * @mul:	Clock multiply.
 * @div:	Clock divider.
 *
 * Return: none.
 */

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
static void set_AHB_APB_div(enum cpu_clk_div div, enum clk_APB1_div APB1_div, enum clk_APB2_div APB2_div)
{
	  LL_RCC_SetAHBPrescaler(div);
	  LL_RCC_SetAPB1Prescaler(APB1_div);
	  LL_RCC_SetAPB2Prescaler(APB2_div);
}
#elif defined ( STM32F030x6 )
static void set_AHB_APB_div(enum cpu_clk_div div, enum clk_APB1_div APB1_div) {
	LL_RCC_SetAHBPrescaler(div);
	LL_RCC_SetAPB1Prescaler(APB1_div);
}
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
bool cpu_clk_init(uint32_t cpu_Hz, enum cpu_clk_src src, enum cpu_clk_mul mul, enum cpu_clk_div div, enum clk_APB1_div APB1_div, enum clk_APB2_div APB2_div, enum clk_adc_div ADC_div)
#elif defined ( STM32F030x6 )
bool cpu_clk_init(uint32_t cpu_Hz, enum cpu_clk_src src, enum cpu_clk_mul mul, enum cpu_clk_div div,
		enum clk_APB1_div APB1_div)
#endif
{
	set_flash_latency(cpu_Hz);
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	clk_enable(CLK_AFIO, APB2);
#endif
	clk_enable(CLK_POWER, APB1);
#elif defined ( STM32F030x6 )
	clk_enable(CLK_SYSCFG, APB1, GRP2);
	clk_enable(CLK_POWER, APB1, GRP1);
#endif

//    nvic_set_priority_grouping(NVIC_PRIORITYGROUP_4);
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	LL_GPIO_AF_Remap_SWJ_NOJTAG();//swd
#endif

	switch (src) {
	case CPU_CLK_HSI:
		LL_RCC_HSI_SetCalibTrimming(16);
		LL_RCC_HSI_Enable();
		while (LL_RCC_HSI_IsReady() != 1) {
		}
		if (mul != CPU_CLK_MUL_NONE) {
			LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, mul);
			LL_RCC_PLL_Enable();
			while (LL_RCC_PLL_IsReady() != 1) {
			}
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
			  set_AHB_APB_div(div, APB1_div, APB2_div);
#elif defined ( STM32F030x6 )
			set_AHB_APB_div(div, APB1_div);
#endif

			LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
			while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
			}
		} else {
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
			  set_AHB_APB_div(div, APB1_div, APB2_div);
#elif defined ( STM32F030x6 )
			set_AHB_APB_div(div, APB1_div);
#endif
			LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
			while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) {
			}
		}
		break;
	case CPU_CLK_HSE:
		LL_RCC_HSE_Enable();
		while (LL_RCC_HSE_IsReady() != 1) {
		}
		if (mul != CPU_CLK_MUL_NONE) {
			LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, mul); //TODO div 1
			LL_RCC_PLL_Enable();
			while (LL_RCC_PLL_IsReady() != 1) {
			}
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
			  set_AHB_APB_div(div, APB1_div, APB2_div);
#elif defined ( STM32F030x6 )
			set_AHB_APB_div(div, APB1_div);
#endif
			LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
			while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
			}
		} else {
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
			  set_AHB_APB_div(div, APB1_div, APB2_div);
#elif defined ( STM32F030x6 )
			set_AHB_APB_div(div, APB1_div);
#endif
			LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSE);
			while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSE) {
			}
		}
#if defined ( STM32F030x6 )
	clk_enable(CLK_PORTF, AHB1, GRP1);
#endif
		break;
	case CPU_CLK_LSI:
		LL_RCC_LSI_Enable();
		while (LL_RCC_LSI_IsReady() != 1) {
		}
		break;
	case CPU_CLK_LSE:
		LL_RCC_LSE_Enable();
		while (LL_RCC_LSE_IsReady() != 1) {
		}
		break;
	}

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	LL_RCC_SetADCClockSource(ADC_div);
#endif

	//TODO Error
	if (get_clock()!= cpu_Hz)
	{
		return false;
	}
	set_flash_latency(cpu_get_clk());
	return true;
}

uint32_t cpu_get_clk(void) {
	return SystemCoreClock;
}



#if defined ( STM32F030x6 ) || defined ( STM32F373xC )
#if defined ( STM32F030x6 )
void adc_clk_14RC_init(void)
{
	LL_RCC_HSI14_Enable();
	  while(LL_RCC_HSI14_IsReady() != 1)
	  {

	  }
	  LL_RCC_HSI14_SetCalibTrimming(16);

	  LL_RCC_HSI14_EnableADCControl();
}
#endif

void set_usart_clk_src(enum usart_clk_src src)
{
	  LL_RCC_SetUSARTClockSource(src);
}

void set_I2C_clk_src(enum I2C_clk_src src)
{
	LL_RCC_SetI2CClockSource(src);
}

void set_RTC_clk_src(enum RTC_clk_src src)
{
	LL_PWR_EnableBkUpAccess();
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(src);
    LL_RCC_EnableRTC();
}
#endif
