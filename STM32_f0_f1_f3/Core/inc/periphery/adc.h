#ifndef __ADC_H__
#define __ADC_H__

#include "stdint.h"
#include "stdbool.h"
#include "port.h"

#if defined ( STM32F030x6 )
#include "stm32f0xx_ll_adc.h"
#elif defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_adc.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_adc.h"
#endif

/* Defines */
#define ADC_MAX		4095
#define ADC_per_mV	(ADC_MAX + 1) / UCC_mV
#define ADC_DATA_MASK	0xFFF

/* Enumerations */
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
enum adc_mode {
	ADC_MODE_INDEP = LL_ADC_MULTI_INDEPENDENT,
	ADC_MODE_DUAL_SIMULT = LL_ADC_MULTI_DUAL_REG_SIMULT,
	ADC_MODE_DUAL_INTERL_FAST=LL_ADC_MULTI_DUAL_REG_INTERL_FAST,
	ADC_MODE_DUAL_INTERL_SLOW=LL_ADC_MULTI_DUAL_REG_INTERL_SLOW,
	ADC_MODE_DUAL_INJ_SIMULT=LL_ADC_MULTI_DUAL_INJ_SIMULT,
	ADC_MODE_DUAL_INJ_ALTERN=LL_ADC_MULTI_DUAL_INJ_ALTERN,
	ADC_MODE_DUAL_SIM_INJ_SIM=LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM,
	ADC_MODE_DUAL_SIM_INJ_ALT=LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT,
	ADC_MODE_DUAL_INTFAST_INJ_SIM=LL_ADC_MULTI_DUAL_REG_INTFAST_INJ_SIM,
	ADC_MODE_DUAL_INTSLOW_INJ_SIM=LL_ADC_MULTI_DUAL_REG_INTSLOW_INJ_SIM
};
#endif

enum adc_name {
	ADC_1 = (uint32_t)ADC1,
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	ADC_2 = (uint32_t)ADC2,
#if defined ( STM32F103xE )
	ADC_3 = (uint32_t)ADC3
#endif
#endif
};

enum adc_channel {
	ADC_CH_0 = LL_ADC_CHANNEL_0,
	ADC_CH_1 = LL_ADC_CHANNEL_1,
	ADC_CH_2 = LL_ADC_CHANNEL_2,
	ADC_CH_3 = LL_ADC_CHANNEL_3,
	ADC_CH_4 = LL_ADC_CHANNEL_4,
	ADC_CH_5 = LL_ADC_CHANNEL_5,
	ADC_CH_6 = LL_ADC_CHANNEL_6,
	ADC_CH_7 = LL_ADC_CHANNEL_7,
	ADC_CH_8 = LL_ADC_CHANNEL_8,
	ADC_CH_9 = LL_ADC_CHANNEL_9,
	ADC_CH_10 = LL_ADC_CHANNEL_10,
	ADC_CH_11 = LL_ADC_CHANNEL_11,
	ADC_CH_12 = LL_ADC_CHANNEL_12,
	ADC_CH_13 = LL_ADC_CHANNEL_13,
	ADC_CH_14 = LL_ADC_CHANNEL_14,
	ADC_CH_15 = LL_ADC_CHANNEL_15,
	ADC_CH_16 = LL_ADC_CHANNEL_16,
	ADC_CH_17 = LL_ADC_CHANNEL_17,
	ADC_VREFINT = LL_ADC_CHANNEL_VREFINT,
	ADC_TEMP = LL_ADC_CHANNEL_TEMPSENSOR
};

enum sampling_time {
	ADC_SAMPLINGTIME_1 = LL_ADC_SAMPLINGTIME_1CYCLE_5,
	ADC_SAMPLINGTIME_7 = LL_ADC_SAMPLINGTIME_7CYCLES_5,
	ADC_SAMPLINGTIME_13 = LL_ADC_SAMPLINGTIME_13CYCLES_5,
	ADC_SAMPLINGTIME_28 = LL_ADC_SAMPLINGTIME_28CYCLES_5,
	ADC_SAMPLINGTIME_41 = LL_ADC_SAMPLINGTIME_41CYCLES_5,
	ADC_SAMPLINGTIME_55 = LL_ADC_SAMPLINGTIME_55CYCLES_5,
	ADC_SAMPLINGTIME_71 = LL_ADC_SAMPLINGTIME_71CYCLES_5,
	ADC_SAMPLINGTIME_239 = LL_ADC_SAMPLINGTIME_239CYCLES_5
};

#if defined ( STM32F030x6 )
enum adc_clk_src {
		ADC_CLK_SRC_ASYNC = LL_ADC_CLOCK_ASYNC,
		ADC_CLK_SRC_PCLK_DIV2 = LL_ADC_CLOCK_SYNC_PCLK_DIV2,
		ADC_CLK_SRC_PCLK_DIV4 = LL_ADC_CLOCK_SYNC_PCLK_DIV4
};
#endif

/* Exported functions */
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
extern void adc_x_init(enum adc_name name, enum adc_mode mode);
#elif defined ( STM32F030x6 )
extern void adc_x_init(enum adc_name name, enum adc_clk_src src);
#endif

extern void adc_1_channel_select(enum adc_channel channel);
extern void adc_1_start(void);
extern bool adc_1_is_ready(void);
extern uint32_t adc_1_get_result(void);
extern uint32_t adc_1_get_data(void);

#if defined (STM32F103xE)
extern void adc_2_channel_select(uint32_t channel);
extern void adc_2_start(void);
extern bool adc_2_is_ready(void);
extern uint32_t adc_2_get_result(void);
extern uint32_t adc_2_get_data(void);
#endif

extern void adc_pin_init(enum port_name port, uint32_t pins);

#endif
