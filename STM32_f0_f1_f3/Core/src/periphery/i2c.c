#include "i2c.h"
#include "delay.h"

void i2c_init(enum i2c_num i2c, uint32_t freg, bool en_int) {
	LL_I2C_InitTypeDef I2C_InitStruct = { 0 };

	LL_I2C_DisableOwnAddress2((I2C_TypeDef*) i2c);
	LL_I2C_DisableGeneralCall((I2C_TypeDef*) i2c);
	LL_I2C_EnableClockStretching((I2C_TypeDef*) i2c);
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
#if defined ( STM32F030x6 )
	I2C_InitStruct.Timing = freg; //TODO
	I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
	I2C_InitStruct.DigitalFilter = 0;
#elif defined ( STM32F103xE ) || defined ( STM32F103xB )
	  I2C_InitStruct.ClockSpeed = freg;
	  I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
#endif
	I2C_InitStruct.OwnAddress1 = 0;
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
	LL_I2C_Init((I2C_TypeDef*) i2c, &I2C_InitStruct);
#if defined ( STM32F030x6 )
	LL_I2C_EnableAutoEndMode((I2C_TypeDef*) i2c);
	LL_I2C_SetOwnAddress2((I2C_TypeDef*) i2c, 0, LL_I2C_OWNADDRESS2_NOMASK);
#elif defined ( STM32F103xE ) || defined ( STM32F103xB )
	  LL_I2C_SetOwnAddress2((I2C_TypeDef*)i2c, 0);
#endif
	if (en_int) {
		LL_I2C_EnableIT_RX((I2C_TypeDef*) i2c);
	}
}

void i2c_start(enum i2c_num i2c) {
	LL_I2C_Enable((I2C_TypeDef*) i2c);
}

void i2c_stop(enum i2c_num i2c) {
	LL_I2C_Disable((I2C_TypeDef*) i2c);
}

/*bool i2c_is_rcv_not_empty(enum i2c_num i2c) {
	if (LL_I2C_IsActiveFlag_RXNE((I2C_TypeDef*) i2c) == SET)
		return true;
	return false;
}*/

bool i2c_Write(enum i2c_num i2c, uint8_t addr, uint8_t *data, uint8_t tcount,
		uint32_t timeout_ms, enum I2c_slave_speed slave_speed) {

	uint32_t temp_7bit_addr = (uint32_t)(addr<<1);
	if (!LL_I2C_IsEnabled((I2C_TypeDef*) i2c)) {
		LL_I2C_Enable((I2C_TypeDef*) i2c);
	}

	if (LL_I2C_IsActiveFlag_BUSY((I2C_TypeDef*) i2c)) {
		goto error;
	}

	uint32_t timeout = get_time();

	LL_I2C_ClearFlag_NACK((I2C_TypeDef*) i2c);

	LL_I2C_HandleTransfer((I2C_TypeDef*) i2c, temp_7bit_addr, LL_I2C_ADDRSLAVE_7BIT,
			tcount, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
	while (tcount)
	{
		switch (slave_speed)
		{
		case FAST:
			break;
		case MEDIUM:
			_delay_us(250);
			break;
		case SLOW:
			_delay_us(500);
			break;
		}
		while (1)
		{
			if (LL_I2C_IsActiveFlag_NACK((I2C_TypeDef*) i2c)) {
				goto error;
			}

			if (LL_I2C_IsActiveFlag_TXIS((I2C_TypeDef*) i2c)) {
				break;
			}

			if (get_time() - timeout >= timeout_ms) {
				goto error;
			}
		}
	LL_I2C_TransmitData8(((I2C_TypeDef*) i2c), *data);
	switch (slave_speed)
	{
	case FAST:
		break;
	case MEDIUM:
		_delay_us(250);
		break;
	case SLOW:
		_delay_us(500);
		break;
	}
	LL_I2C_ClearFlag_NACK((I2C_TypeDef*) i2c);

	tcount--;
	if(tcount)data++;

	}

LL_I2C_ClearFlag_STOP((I2C_TypeDef*) i2c);
LL_I2C_ClearFlag_TXE((I2C_TypeDef*) i2c);
return true;

	error: {
		LL_I2C_GenerateStopCondition(((I2C_TypeDef*) i2c));
		LL_I2C_ClearFlag_STOP((I2C_TypeDef*) i2c);
		LL_I2C_ClearFlag_TXE((I2C_TypeDef*) i2c);
		LL_I2C_Disable((I2C_TypeDef*) i2c);
		return false;
	}
}

bool i2c_Read(enum i2c_num i2c, uint8_t addr, uint8_t *data, uint8_t rcount,
		uint32_t timeout_ms,  enum I2c_slave_speed slave_speed) {

	uint32_t temp_7bit_addr = (uint32_t)(addr<<1);
	if (!LL_I2C_IsEnabled((I2C_TypeDef*) i2c)) {
		LL_I2C_Enable((I2C_TypeDef*) i2c);
	}

	if (LL_I2C_IsActiveFlag_BUSY((I2C_TypeDef*) i2c)) {
		goto error;
	}

	uint32_t timeout = get_time();

	LL_I2C_ClearFlag_NACK((I2C_TypeDef*) i2c);

	LL_I2C_HandleTransfer((I2C_TypeDef*) i2c, temp_7bit_addr, LL_I2C_ADDRSLAVE_7BIT,
			rcount, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);
	while (rcount)
	{
		switch (slave_speed)
		{
		case FAST:
			break;
		case MEDIUM:
			_delay_us(250);
			break;
		case SLOW:
			_delay_us(500);
			break;
		}
		while (1)
		{
			if (LL_I2C_IsActiveFlag_NACK((I2C_TypeDef*) i2c)) {
				goto error;
			}

			if (LL_I2C_IsActiveFlag_RXNE((I2C_TypeDef*) i2c)) {
				break;
			}

			if (get_time() - timeout >= timeout_ms) {
				goto error;
			}
		}
	*data = LL_I2C_ReceiveData8((I2C_TypeDef*) i2c);
	LL_I2C_ClearFlag_NACK((I2C_TypeDef*) i2c);

	rcount--;
	if(rcount)data++;

	}

LL_I2C_ClearFlag_STOP((I2C_TypeDef*) i2c);
LL_I2C_ClearFlag_TXE((I2C_TypeDef*) i2c);
return true;

	error: {
		LL_I2C_GenerateStopCondition(((I2C_TypeDef*) i2c));
		LL_I2C_ClearFlag_STOP((I2C_TypeDef*) i2c);
		LL_I2C_ClearFlag_TXE((I2C_TypeDef*) i2c);
		LL_I2C_Disable((I2C_TypeDef*) i2c);
		return false;
	}
}
