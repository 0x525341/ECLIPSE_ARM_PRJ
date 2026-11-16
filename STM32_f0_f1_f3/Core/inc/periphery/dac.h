/*
 * dac.h - Functions for working with DAC
 *
 * Copyright (C) 2014 ELP
 * Author: Eldar Khayrullin <dep033@rambler.ru>
 *
 * This program is proprietary software.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef __DAC_H__
#define __DAC_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE )
#include "stm32f1xx_ll_dac.h"
#endif

#include "port.h"

/* Defines */
#define DAC_MAX		4095
#define DAC_DELAY_us	5.2

/* Enumerations */
#if defined ( STM32F103xE )
enum  dac_pin {
	DAC1_OUT_PIN = PIN_4,
	DAC2_OUT_PIN = PIN_5
};
#endif
/* Exported functions */
#if defined ( STM32F103xE )
extern void dac_init(enum dac_pin pin);
extern void dac_pin_init(uint32_t dac_pins);
extern void dac_ch1_set_data(uint32_t data);
extern void dac_ch2_set_data(uint32_t data);
extern void dac_start(enum  dac_pin pin);
#endif

#endif
