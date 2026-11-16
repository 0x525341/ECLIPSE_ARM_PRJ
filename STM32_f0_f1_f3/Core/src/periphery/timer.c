#include "timer.h"

/**
 * timer_init() - initialize Timer
 *
 * Return: none.
 */

void timer_counter_init(enum timer_name timer, uint16_t prescaler,
		uint32_t period, enum timer_clk_div div) {
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };

	TIM_InitStruct.Prescaler = prescaler;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_InitStruct.Autoreload = period;
	TIM_InitStruct.ClockDivision = div;
	TIM_InitStruct.RepetitionCounter = 0;

	LL_TIM_Init((TIM_TypeDef*) timer, &TIM_InitStruct);

	LL_TIM_DisableARRPreload((TIM_TypeDef*) timer);
//	  LL_TIM_SetClockSource((TIM_TypeDef*)timer, LL_TIM_CLOCKSOURCE_INTERNAL);

	LL_TIM_SetTriggerOutput((TIM_TypeDef*) timer, LL_TIM_TRGO_RESET);
	LL_TIM_DisableMasterSlaveMode((TIM_TypeDef*) timer);
}

void timer_enable_it(enum timer_name timer) {
	LL_TIM_EnableIT_UPDATE((TIM_TypeDef*) timer);
}

void timer_enable_it_trigger(enum timer_name timer) {
	LL_TIM_EnableIT_TRIG((TIM_TypeDef*) timer);
}

void timer_disable_it(enum timer_name timer) {
	LL_TIM_DisableIT_UPDATE((TIM_TypeDef*) timer);
}

void timer_set_edge_trigger(enum timer_name timer) {
	LL_TIM_SetTriggerInput((TIM_TypeDef*) timer, LL_TIM_TS_TI1F_ED);
}

void timer_pwm_mode_init(enum timer_name timer, enum timer_channel channel) {
	LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = { 0 };

	LL_TIM_OC_EnablePreload((TIM_TypeDef*) timer, channel);

	TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
	TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
	TIM_OC_InitStruct.CompareValue = 0;
	TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
	TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
	LL_TIM_OC_Init((TIM_TypeDef*) timer, channel, &TIM_OC_InitStruct);

	LL_TIM_OC_DisableFast((TIM_TypeDef*) timer, channel);

	LL_TIM_CC_EnableChannel((TIM_TypeDef*) timer, channel);
	LL_TIM_EnableAutomaticOutput((TIM_TypeDef*) timer);
}

void timer_pwm_mode_deadtime_init(enum timer_name timer) {
	LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = { 0 };

	TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
	TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
	TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
	TIM_BDTRInitStruct.DeadTime = 0;
	TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
	TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
	TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
	LL_TIM_BDTR_Init((TIM_TypeDef*) timer, &TIM_BDTRInitStruct);
}

void timer_encoder_mode_init(enum timer_name timer, enum timer_channel channel) {
	LL_TIM_SetEncoderMode((TIM_TypeDef*) timer, LL_TIM_ENCODERMODE_X2_TI1);
	LL_TIM_IC_SetActiveInput((TIM_TypeDef*) timer, channel, LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetPrescaler((TIM_TypeDef*) timer, channel, LL_TIM_ICPSC_DIV1);
	LL_TIM_IC_SetFilter((TIM_TypeDef*) timer, channel, LL_TIM_IC_FILTER_FDIV1);
	LL_TIM_IC_SetPolarity((TIM_TypeDef*) timer, channel, LL_TIM_IC_POLARITY_FALLING);
}

void timer_pwm_set(enum timer_name timer, enum timer_channel channel,
		uint32_t fill) {
	switch (channel) {
	case TIMER_CH1:
		LL_TIM_OC_SetCompareCH1((TIM_TypeDef*) timer, fill);
		break;
	case TIMER_CH2:
		LL_TIM_OC_SetCompareCH2((TIM_TypeDef*) timer, fill);
		break;
	case TIMER_CH3:
		LL_TIM_OC_SetCompareCH3((TIM_TypeDef*) timer, fill);
		break;
	case TIMER_CH4:
		LL_TIM_OC_SetCompareCH4((TIM_TypeDef*) timer, fill);
		break;
	}
}

void timer_start(enum timer_name timer) {
	LL_TIM_EnableCounter((TIM_TypeDef*) timer);
}

void timer_stop(enum timer_name timer) {
	LL_TIM_DisableCounter((TIM_TypeDef*) timer);
}

void timer_clear_all_it_events(enum timer_name timer) {
	LL_TIM_ClearFlag_UPDATE((TIM_TypeDef*) timer);
	LL_TIM_ClearFlag_TRIG((TIM_TypeDef*) timer);
}

uint32_t timer_get_cnt(enum timer_name timer) {
	return LL_TIM_GetCounter((TIM_TypeDef*) timer);
}

void timer_set_cnt(enum timer_name timer, uint32_t Counter) {
	LL_TIM_SetCounter((TIM_TypeDef*) timer, Counter);
}
