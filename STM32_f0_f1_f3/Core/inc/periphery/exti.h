#ifndef __EXTI_H__
#define __EXTI_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_system.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_system.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_system.h"
#endif

/* Defines */

/* Enumerations */
enum syscfg_exti_port
{
	EXTI_PORT_A = LL_SYSCFG_EXTI_PORTA,
	EXTI_PORT_B = LL_SYSCFG_EXTI_PORTB,
	EXTI_PORT_C = LL_SYSCFG_EXTI_PORTC,
	EXTI_PORT_D = LL_SYSCFG_EXTI_PORTD,
	EXTI_PORT_F = LL_SYSCFG_EXTI_PORTF,

};

enum syscfg_exti_line
{
	SYSCFG_EXTI_LINE0 = LL_SYSCFG_EXTI_LINE0,
	SYSCFG_EXTI_LINE1 = LL_SYSCFG_EXTI_LINE1,
	SYSCFG_EXTI_LINE2 = LL_SYSCFG_EXTI_LINE2,
	SYSCFG_EXTI_LINE3 = LL_SYSCFG_EXTI_LINE3,
	SYSCFG_EXTI_LINE4 = LL_SYSCFG_EXTI_LINE4,
	SYSCFG_EXTI_LINE5 = LL_SYSCFG_EXTI_LINE5,
	SYSCFG_EXTI_LINE6 = LL_SYSCFG_EXTI_LINE6,
	SYSCFG_EXTI_LINE7 = LL_SYSCFG_EXTI_LINE7,
	SYSCFG_EXTI_LINE8 = LL_SYSCFG_EXTI_LINE8,
	SYSCFG_EXTI_LINE9 = LL_SYSCFG_EXTI_LINE9,
	SYSCFG_EXTI_LINE10 = LL_SYSCFG_EXTI_LINE10,
	SYSCFG_EXTI_LINE11 = LL_SYSCFG_EXTI_LINE11,
	SYSCFG_EXTI_LINE12 = LL_SYSCFG_EXTI_LINE12,
	SYSCFG_EXTI_LINE13 = LL_SYSCFG_EXTI_LINE13,
	SYSCFG_EXTI_LINE14 = LL_SYSCFG_EXTI_LINE14,
	SYSCFG_EXTI_LINE15 = LL_SYSCFG_EXTI_LINE15,
};

enum exti_line
{
	EXTI_LINE0 = LL_EXTI_LINE_0,
	EXTI_LINE1 = LL_EXTI_LINE_1,
	EXTI_LINE2 = LL_EXTI_LINE_2,
	EXTI_LINE3 = LL_EXTI_LINE_3,
	EXTI_LINE4 = LL_EXTI_LINE_4,
	EXTI_LINE5 = LL_EXTI_LINE_5,
	EXTI_LINE6 = LL_EXTI_LINE_6,
	EXTI_LINE7 = LL_EXTI_LINE_7,
	EXTI_LINE8 = LL_EXTI_LINE_8,
	EXTI_LINE9 = LL_EXTI_LINE_9,
	EXTI_LINE10 = LL_EXTI_LINE_10,
	EXTI_LINE11 = LL_EXTI_LINE_11,
	EXTI_LINE12 = LL_EXTI_LINE_12,
	EXTI_LINE13 = LL_EXTI_LINE_13,
	EXTI_LINE14 = LL_EXTI_LINE_14,
	EXTI_LINE15 = LL_EXTI_LINE_15,
};

enum exti_edge_trigger
{
	TRIGGER_NONE = LL_EXTI_TRIGGER_NONE,
	TRIGGER_RISING = LL_EXTI_TRIGGER_RISING,
	TRIGGER_FALLING = LL_EXTI_TRIGGER_FALLING,
	TRIGGER_RISING_FALLING = LL_EXTI_TRIGGER_RISING_FALLING,
};

enum exti_mode
{
	MODE_IT = LL_EXTI_MODE_IT,
	MODE_EVENT = LL_EXTI_MODE_EVENT,
	MODE_IT_EVENT = LL_EXTI_MODE_IT_EVENT,
};
/* Exported functions */

extern void exti_pin_init(enum syscfg_exti_port port, enum syscfg_exti_line syscfg_line, enum exti_line line, enum exti_mode mode, enum exti_edge_trigger trigger);
extern bool exti_is_active_flag(enum exti_line line);
extern void exti_clear_flag(enum exti_line line);
extern void exti_set_trigger(enum exti_line line, enum exti_edge_trigger trigger);
extern bool exti_is_set_trigger(enum exti_line line, enum exti_edge_trigger trigger);

#endif
