#ifndef __I2C_H__
#define __I2C_H__

#include "stdint.h"
#include "stdbool.h"


#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_i2c.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_i2c.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_i2c.h"
#endif

#define I2C_1_HANDLER		void I2C1_IRQHandler(void)
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
#define I2C_2_HANDLER		void I2C2_IRQHandler(void)
#endif

enum i2c_num {
	I2C_1 = (uint32_t)I2C1,
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	I2C_2 = (uint32_t)I2C2
#endif
};

enum I2c_slave_speed
{
	FAST,
	MEDIUM,
	SLOW
};

extern void i2c_init(enum i2c_num i2c, uint32_t freg, bool en_int);
extern void i2c_start(enum i2c_num i2c);
extern void i2c_stop(enum i2c_num i2c);
extern bool i2c_Write(enum i2c_num i2c, uint8_t addr, uint8_t *data, uint8_t tcount,
		uint32_t timeout_ms, enum I2c_slave_speed slave_speed);
extern bool i2c_Read(enum i2c_num i2c, uint8_t addr, uint8_t *data, uint8_t rcount,
		uint32_t timeout_ms,  enum I2c_slave_speed slave_speed);
extern bool i2c_is_rcv_not_empty(enum i2c_num i2c);

#endif
