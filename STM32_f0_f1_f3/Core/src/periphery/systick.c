#include "systick.h"
#include "cpu.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "core_cm3.h"
#elif defined ( STM32F030x6 )
#include "core_cm0.h"
#elif defined ( STM32F373xC )
#include "core_cm4.h"
#endif

handler systick_handler;

/**
 * systick_init() - initialize SysTick
 * @period_ms:	Period in ms.
 *
 * Return: none.
 */
void systick_init(uint32_t period_ms, handler func)
{
	uint32_t clock = cpu_get_clk();
	SysTick_Config(clock / 1000 * period_ms);
	systick_handler = func;
}

/**
 * SysTick_Handler() - SysTick interrupt handler
 *
 * Return: none.
 */
void SysTick_Handler(void)
{
	if (systick_handler != NULL)
		systick_handler();
}
