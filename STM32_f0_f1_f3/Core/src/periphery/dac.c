#include "dac.h"

#if defined ( STM32F103xE )
#define DAC_PORT PORT_A
#endif
/**
 * dac_init() - initialize DAC
 * @mode:	Channels mode.
 *
 * Return: none.
 */
#if defined ( STM32F103xE )
void dac_init(enum dac_pin pin)
{
	  LL_DAC_InitTypeDef DAC_InitStruct = {0};
	  DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	  DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	  DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;
	  switch (pin)
	  {
	  case DAC1_OUT_PIN:
		  LL_DAC_Init(DAC, LL_DAC_CHANNEL_1, &DAC_InitStruct);
		  LL_DAC_DisableTrigger(DAC, LL_DAC_CHANNEL_1);
		  break;
	  case DAC2_OUT_PIN:
		  LL_DAC_Init(DAC, LL_DAC_CHANNEL_2, &DAC_InitStruct);
		  LL_DAC_DisableTrigger(DAC, LL_DAC_CHANNEL_2);
		  break;
	  }
}
#endif
/**
 * dac_pin_init() - initialize DAC pin
 * @dac_pins:	DAC pins.
 *
 * Return: none.
 */
#if defined ( STM32F103xE )
void dac_pin_init(uint32_t dac_pins)
{
	port_pin_init(DAC_PORT, dac_pins, PIN_MODE_ANALOG, PIN_TYPE_IN,
			      PIN_PULL_NOT, PIN_SPEED_NOT, PIN_RESET);
}
#endif
/**
 * dac_ch1_set_data() - set data to DAC channel 1
 * @data:	Data.
 *
 * Return: none.
 */
#if defined ( STM32F103xE )
void dac_ch1_set_data(uint32_t data)
{
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, data);
}
#endif
/**
 * dac_ch2_set_data() - set data to DAC channel 2
 * @data:	Data.
 *
 * Return: none.
 */
#if defined ( STM32F103xE )
void dac_ch2_set_data(uint32_t data)
{
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, data);
}
#endif
/**
 * dac_start() - start DAC
 *
 * Return: none.
 */
#if defined ( STM32F103xE )
void dac_start(enum  dac_pin pin)
{
	switch (pin) {
		case DAC1_OUT_PIN:
			LL_DAC_Enable(DAC, LL_DAC_CHANNEL_1);
			break;
		case DAC2_OUT_PIN:
			LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
			break;
	}
}
#endif
