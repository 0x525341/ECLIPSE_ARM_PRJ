#include "exti.h"

void exti_pin_init(enum syscfg_exti_port port, enum syscfg_exti_line syscfg_line, enum exti_line line, enum exti_mode mode, enum exti_edge_trigger trigger)
{
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
	LL_SYSCFG_SetEXTISource(port, syscfg_line);

	EXTI_InitStruct.Line_0_31 = line;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = mode;
	EXTI_InitStruct.Trigger = trigger;
	LL_EXTI_Init(&EXTI_InitStruct);
}

void exti_set_trigger(enum exti_line line, enum exti_edge_trigger trigger)
{
	switch (trigger)
	{
	case TRIGGER_NONE:
		LL_EXTI_DisableFallingTrig_0_31(line);
		LL_EXTI_DisableRisingTrig_0_31(line);
		break;
	case TRIGGER_RISING:
		LL_EXTI_DisableFallingTrig_0_31(line);
		LL_EXTI_EnableRisingTrig_0_31(line);
		break;
	case TRIGGER_FALLING:
		LL_EXTI_DisableRisingTrig_0_31(line);
		LL_EXTI_EnableFallingTrig_0_31(line);
		break;
	case TRIGGER_RISING_FALLING:
		LL_EXTI_EnableRisingTrig_0_31(line);
		LL_EXTI_EnableFallingTrig_0_31(line);
		break;
	}
}

bool exti_is_set_trigger(enum exti_line line, enum exti_edge_trigger trigger)
{
	switch (trigger)
	{
	case TRIGGER_RISING:
		return (bool)LL_EXTI_IsEnabledRisingTrig_0_31(line);
		break;
	case TRIGGER_FALLING:
		return (bool)LL_EXTI_IsEnabledFallingTrig_0_31(line);
		break;
	}
	return false;
}

bool exti_is_active_flag(enum exti_line line)
{
	return (bool)LL_EXTI_IsActiveFlag_0_31(line);
}

void exti_clear_flag(enum exti_line line)
{
	LL_EXTI_ClearFlag_0_31(line);
}

