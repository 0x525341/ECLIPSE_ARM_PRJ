#ifndef __TIMER_H__
#define __TIMER_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_tim.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_tim.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_tim.h"
#endif

/* Defines */
/* Enumerations */
enum timer_name {
#ifndef STM32F373xC
	TIMER_1 = (uint32_t)TIM1,
#endif

#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	TIMER_2 = (uint32_t)TIM2,
#endif
	TIMER_3 = (uint32_t)TIM3,
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	TIMER_4 = (uint32_t)TIM4,
#endif
#if defined ( STM32F103xE ) || defined ( STM32F373xC )
	TIMER_5 = (uint32_t)TIM5,
	TIMER_6 = (uint32_t)TIM6,
	TIMER_7 = (uint32_t)TIM7,
#endif

#if defined ( STM32F103xE )
	TIMER_8 = (uint32_t)TIM8,
#endif

#if defined ( STM32F373xC )
	TIMER_12= (uint32_t)TIM12,
	TIMER_13 = (uint32_t)TIM13,
	TIMER_14 = (uint32_t)TIM14,
#endif

#if defined ( STM32F030x6 ) || defined ( STM32F373xC )
	TIMER_14 = (uint32_t)TIM14,
	TIMER_16 = (uint32_t)TIM16,
	TIMER_17 = (uint32_t)TIM17,
#endif

#if defined ( STM32F373xC )
	TIMER_18 = (uint32_t)TIM18,
	TIMER_19 = (uint32_t)TIM19,
#endif
};

enum timer_clk_div {
	TIMER_CLK_DIV_1 = LL_TIM_CLOCKDIVISION_DIV1,
	TIMER_CLK_DIV_2 = LL_TIM_CLOCKDIVISION_DIV2,
	TIMER_CLK_DIV_4 = LL_TIM_CLOCKDIVISION_DIV4,
};

enum timer_channel {
	TIMER_CH1 = LL_TIM_CHANNEL_CH1,
	TIMER_CH1N = LL_TIM_CHANNEL_CH1N,
	TIMER_CH2 = LL_TIM_CHANNEL_CH2,
	TIMER_CH2N = LL_TIM_CHANNEL_CH2N,
	TIMER_CH3 = LL_TIM_CHANNEL_CH3,
	TIMER_CH3N = LL_TIM_CHANNEL_CH3N,
	TIMER_CH4 = LL_TIM_CHANNEL_CH4,
};

enum timer_ch_psc {
	TIMER_CH_PSC_NONE = LL_TIM_ICPSC_DIV1,
	TIMER_CH_PSC_2 = LL_TIM_ICPSC_DIV2,
	TIMER_CH_PSC_4 = LL_TIM_ICPSC_DIV4,
	TIMER_CH_PSC_8 = LL_TIM_ICPSC_DIV8
};

/* Exported functions */
extern void timer_counter_init(enum timer_name timer, uint16_t prescaler, uint32_t period, enum timer_clk_div div);
extern void timer_enable_it(enum timer_name timer);
extern void timer_disable_it(enum timer_name timer);
extern void timer_pwm_mode_init(enum timer_name timer, enum timer_channel channel);
extern void timer_pwm_mode_deadtime_init(enum timer_name timer);
extern void timer_encoder_mode_init(enum timer_name timer, enum timer_channel channel);
extern void timer_pwm_set(enum timer_name timer, enum timer_channel channel,
			  uint32_t fill);
extern void timer_start(enum timer_name timer);
extern void timer_stop(enum timer_name timer);
//extern void timer_ext_event_it(enum timer_name timer,
//			       enum timer_channel channel, bool enable);
extern void timer_clear_all_it_events(enum timer_name timer);
extern void timer_enable_it_trigger(enum timer_name timer);
extern uint32_t timer_get_cnt(enum timer_name timer);
extern void timer_set_cnt(enum timer_name timer, uint32_t Counter);
extern void timer_set_edge_trigger(enum timer_name timer);
#endif
