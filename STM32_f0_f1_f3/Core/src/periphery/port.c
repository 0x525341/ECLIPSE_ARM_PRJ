#include "port.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
void port_pin_init(enum port_name port, uint32_t pins,
		   enum pin_mode mode, enum pin_type type,
		   enum pin_pull pull, enum pin_speed speed, enum pin_state state)
#elif defined ( STM32F030x6 ) || defined ( STM32F373xC )
void port_pin_init(enum port_name port, uint32_t pins, enum pin_mode mode,
		enum pin_type type, enum pin_pull pull, enum pin_speed speed,
		enum pin_alternate_func alternate_func, enum pin_state state)
#endif
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (type != PIN_TYPE_IN) {
		if (state == PIN_SET)
			port_pin_set(port, pins);
		else
			port_pin_reset(port, pins);
	}

	GPIO_InitStruct.Pin = pins;
	GPIO_InitStruct.Mode = mode;

#if defined ( STM32F030x6 ) || defined ( STM32F373xC )
	if (mode == PIN_MODE_ALTER) {
		GPIO_InitStruct.Alternate = alternate_func;
	}
#endif

	if (type != PIN_TYPE_IN) {
		GPIO_InitStruct.Speed = speed;
		GPIO_InitStruct.OutputType = type;
	}

	if (pull != PIN_PULL_NOT) {
		GPIO_InitStruct.Pull = pull;
	}

	LL_GPIO_Init((GPIO_TypeDef*) port, &GPIO_InitStruct);
}
/**
 * port_pin_is_set() - check pin is set
 * @port:	Name of port.
 * @pin:	Pin number.
 *
 * Return: true - if pin is set, false - if pin is unset.
 */
bool port_pin_is_set(enum port_name port, uint32_t pin) {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	return (bool) LL_GPIO_IsInputPinSet((GPIO_TypeDef*) port, pin);
#endif
}

/**
 * port_read() - read port data
 * @port:	Name of port.
 *
 * Return: readed data from port.
 */
uint32_t port_read(enum port_name port) {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	return LL_GPIO_ReadInputPort((GPIO_TypeDef*) port);
#endif

}

/**
 * port_write() - write data to port
 * @port:	Name of port.
 * @data:	Data to write.
 *
 * Return: none.
 */
void port_write(enum port_name port, uint32_t data) {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	LL_GPIO_WriteOutputPort((GPIO_TypeDef*) port, data);
#endif

}

/**
 * port_pin_set() - set port pins
 * @port:	Name of port.
 * @pins:	Pins number.
 *
 * Return: none.
 */
void port_pin_set(enum port_name port, uint32_t pins) {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	LL_GPIO_SetOutputPin((GPIO_TypeDef*) port, pins);
#endif
}

/**
 * port_pin_reset() - reset port pins
 * @port:	Name of port.
 * @pins:	Pins number.
 *
 * Return: none.
 */
void port_pin_reset(enum port_name port, uint32_t pins) {
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F030x6 ) || defined ( STM32F373xC )
	LL_GPIO_ResetOutputPin((GPIO_TypeDef*) port, pins);
#endif
}
