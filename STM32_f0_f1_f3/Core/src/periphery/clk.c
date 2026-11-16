#include "clk.h"

/**
 * clk_enable() - clock peripheral
 * @clk_peripherals:	Peripherals to clock.
 *
 * Return: none.
 */

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
void clk_enable(uint32_t clk_peripherals, enum APB_num apb)
{
	switch(apb)
	{
	case APB1:
		LL_APB1_GRP1_EnableClock(clk_peripherals);
		break;
	case APB2:
		LL_APB2_GRP1_EnableClock(clk_peripherals);
		break;
	}
}
#elif defined ( STM32F030x6 )
void clk_enable(uint32_t clk_peripherals, enum APB_num apb, enum GRP_num grp)
{
	switch(apb)
	{
	case APB1:
		switch(grp)
		{
		case GRP1:
		LL_APB1_GRP1_EnableClock(clk_peripherals);
		break;
		case GRP2:
		LL_APB1_GRP2_EnableClock(clk_peripherals);
		break;
		}
		break;
	case AHB1:
		LL_AHB1_GRP1_EnableClock(clk_peripherals);
		break;
	}
}
#endif
