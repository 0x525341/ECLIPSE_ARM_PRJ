#ifndef __PORT_H__
#define __PORT_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F030x6 )
#include "stm32f0xx_ll_gpio.h"
#elif defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_gpio.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_gpio.h"
#endif

/* Defines */

/* Enumerations */
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum /* pin */ {
	PIN_0 = LL_GPIO_PIN_0,
	PIN_1 = LL_GPIO_PIN_1,
	PIN_2 = LL_GPIO_PIN_2,
	PIN_3 = LL_GPIO_PIN_3,
	PIN_4 = LL_GPIO_PIN_4,
	PIN_5 = LL_GPIO_PIN_5,
	PIN_6 = LL_GPIO_PIN_6,
	PIN_7 = LL_GPIO_PIN_7,
	PIN_8 = LL_GPIO_PIN_8,
	PIN_9 = LL_GPIO_PIN_9,
	PIN_10 = LL_GPIO_PIN_10,
	PIN_11 = LL_GPIO_PIN_11,
	PIN_12 = LL_GPIO_PIN_12,
	PIN_13 = LL_GPIO_PIN_13,
	PIN_14 = LL_GPIO_PIN_14,
	PIN_15 = LL_GPIO_PIN_15
};
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum port_name {
	PORT_A = (uint32_t)GPIOA,
	PORT_B = (uint32_t)GPIOB,
	PORT_C = (uint32_t)GPIOC,
	PORT_D = (uint32_t)GPIOD,
#if defined ( STM32F103xE ) || defined ( STM32F373xC )
	PORT_F = (uint32_t)GPIOF,
#endif
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	PORT_E = (uint32_t)GPIOE,
#if defined ( STM32F103xE )
	PORT_G = (uint32_t)GPIOG
#endif
#endif
};
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum pin_mode {
	PIN_MODE_ANALOG = LL_GPIO_MODE_ANALOG,
	PIN_MODE_INPUT = LL_GPIO_MODE_INPUT,
	PIN_MODE_OUTPUT = LL_GPIO_MODE_OUTPUT,
	PIN_MODE_ALTER = LL_GPIO_MODE_ALTERNATE,
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	PIN_MODE_FLOATING = LL_GPIO_MODE_FLOATING,
#endif
};
#endif


enum pin_type {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	PIN_TYPE_IN = -1,
	PIN_TYPE_OUT_PUSHPULL = LL_GPIO_OUTPUT_PUSHPULL,
	PIN_TYPE_OUT_OPENDRAIN = LL_GPIO_OUTPUT_OPENDRAIN
#endif
};

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum pin_pull {
	PIN_PULL_NOT = -1,
	PIN_PULL_UP = LL_GPIO_PULL_UP,
	PIN_PULL_DOWN = LL_GPIO_PULL_DOWN
};
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum pin_speed {
	PIN_SPEED_NOT = -1,
	PIN_SPEED_LOW = LL_GPIO_SPEED_FREQ_LOW,
	PIN_SPEED_MEDIUM = LL_GPIO_SPEED_FREQ_MEDIUM,
	PIN_SPEED_HIGH = LL_GPIO_SPEED_FREQ_HIGH
};
#endif

#if defined ( STM32F030x6 ) || defined ( STM32F373xC )
enum pin_alternate_func {
	PIN_AF_NOT = -1,
	PIN_AF_0 = LL_GPIO_AF_0,
	PIN_AF_1 = LL_GPIO_AF_1,
	PIN_AF_2 = LL_GPIO_AF_2,
	PIN_AF_3 = LL_GPIO_AF_3,
	PIN_AF_4 = LL_GPIO_AF_4,
	PIN_AF_5 = LL_GPIO_AF_5,
	PIN_AF_6 = LL_GPIO_AF_6,
	PIN_AF_7 = LL_GPIO_AF_7,
#if defined ( STM32F373xC )
	PIN_AF_8 = LL_GPIO_AF_8,
	PIN_AF_9 = LL_GPIO_AF_9,
	PIN_AF_10 = LL_GPIO_AF_10,
	PIN_AF_11 = LL_GPIO_AF_11,
	PIN_AF_12 = LL_GPIO_AF_12,
	PIN_AF_13 = LL_GPIO_AF_13,
	PIN_AF_14 = LL_GPIO_AF_14,
	PIN_AF_15 = LL_GPIO_AF_15,
#endif
};
#endif

enum pin_state {
	PIN_RESET,
	PIN_SET
};

/* Exported functions */
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
extern void port_pin_init(enum port_name port, uint32_t pins,
		   enum pin_mode mode, enum pin_type type,
		   enum pin_pull pull, enum pin_speed speed, enum pin_state state);
#elif defined ( STM32F030x6 ) || defined ( STM32F373xC )
extern void port_pin_init(enum port_name port, uint32_t pins, enum pin_mode mode,
		enum pin_type type, enum pin_pull pull, enum pin_speed speed,
		enum pin_alternate_func alternate_func, enum pin_state state);
#endif
extern bool port_pin_is_set(enum port_name port, uint32_t pin);
extern uint32_t port_read(enum port_name port);
extern void port_write(enum port_name port, uint32_t data);
extern void port_pin_set(enum port_name port, uint32_t pins);
extern void port_pin_reset(enum port_name port, uint32_t pins);

#endif
