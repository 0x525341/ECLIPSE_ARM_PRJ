#include "adc.h"

/**
 * adc_init() - initialize ADC
 *
 * Return: none.
 */

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
void adc_x_init(enum adc_name name, enum adc_mode mode)
#elif defined ( STM32F030x6 )
void adc_x_init(enum adc_name name, enum adc_clk_src src)
#elif defined ( STM32F373xC )
void adc_x_init(enum adc_name name)
#endif
{
	LL_ADC_InitTypeDef ADC_InitStruct = {0};
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
#endif
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};

	  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	  ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
#elif defined ( STM32F030x6 )
	  ADC_InitStruct.Clock = src;
	  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	  ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
#endif
	  LL_ADC_Init((ADC_TypeDef*)name, &ADC_InitStruct);

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	  ADC_CommonInitStruct.Multimode = mode;
	  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE((ADC_TypeDef*)name), &ADC_CommonInitStruct);
#endif
	  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
#endif
	  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
#if defined ( STM32F373xC )
	  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
#endif
#if defined ( STM32F030x6 )
	  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
#endif
	  LL_ADC_REG_Init((ADC_TypeDef*)name, &ADC_REG_InitStruct);

#if defined ( STM32F030x6 )
	  LL_ADC_REG_SetSequencerScanDirection((ADC_TypeDef*)name, LL_ADC_REG_SEQ_SCAN_DIR_FORWARD);
	  LL_ADC_SetSamplingTimeCommonChannels((ADC_TypeDef*)name, LL_ADC_SAMPLINGTIME_1CYCLE_5);
#endif

#if defined ( STM32F030x6 )  || defined ( STM32F103xE ) || defined ( STM32F373xC )
		LL_ADC_Enable((ADC_TypeDef*)name);
#endif
//	  u32 wait_loop_index = ((LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES * 32) >> 1);
//	  while(wait_loop_index != 0)
//	  {
//	    wait_loop_index--;
//	  }
	    LL_ADC_StartCalibration((ADC_TypeDef*)name);
	    while (LL_ADC_IsCalibrationOnGoing((ADC_TypeDef*)name) != 0) {}

#if defined ( STM32F030x6 )  || defined ( STM32F103xE ) || defined ( STM32F373xC )
		LL_ADC_Enable((ADC_TypeDef*)name);
#endif
}

void adc_1_channel_select(enum adc_channel channel)
{
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, channel);
	LL_ADC_SetChannelSamplingTime(ADC1, channel, LL_ADC_SAMPLINGTIME_1CYCLE_5);
#endif
#if defined ( STM32F030x6 )
	LL_ADC_REG_SetSequencerChannels(ADC1, channel);
#endif
}

void adc_1_start(void)
{
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
	LL_ADC_REG_StartConversionSWStart(ADC1);
#elif defined ( STM32F030x6 ) || defined ( STM32F373xC )
	LL_ADC_REG_StartConversion(ADC1);
#endif
}

bool adc_1_is_ready(void)
{
	return (bool)LL_ADC_IsActiveFlag_EOS(ADC1);
}

uint32_t adc_1_get_result(void)
{
	LL_ADC_ClearFlag_EOS(ADC1);
	return LL_ADC_REG_ReadConversionData32(ADC1);
}

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
void adc_2_channel_select(uint32_t channel)
{
	LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, channel);
	LL_ADC_SetChannelSamplingTime(ADC2, channel, LL_ADC_SAMPLINGTIME_1CYCLE_5);
}

void adc_2_start(void)
{
	LL_ADC_REG_StartConversionSWStart(ADC2);
}

bool adc_2_is_ready(void)
{
	return (bool)LL_ADC_IsActiveFlag_EOS(ADC2);
}

uint32_t adc_2_get_result(void)
{
	LL_ADC_ClearFlag_EOS(ADC2);
	return LL_ADC_REG_ReadConversionData12(ADC2);
}

uint32_t adc_2_get_data(void)
{
	LL_ADC_ClearFlag_EOS(ADC2);
	return LL_ADC_REG_ReadConversionData12(ADC2) & ADC_DATA_MASK;
}
#endif
/**
 * adc_pin_init() - initialize ADC pin
 * @adc_chs:	ADC channels.
 *
 * Return: none.
 */
void adc_pin_init(enum port_name port, uint32_t pins)
{
#if defined ( STM32F103xE ) || defined ( STM32F103xB )
port_pin_init(port, pins, PIN_MODE_ANALOG,
		PIN_TYPE_IN, PIN_PULL_NOT, PIN_SPEED_NOT, PIN_RESET);
#elif defined ( STM32F030x6 ) || defined ( STM32F373xC )
port_pin_init(port, pins, PIN_MODE_ANALOG,
		PIN_TYPE_IN, PIN_PULL_NOT, PIN_SPEED_NOT, PIN_AF_NOT, PIN_RESET);
#endif
}
