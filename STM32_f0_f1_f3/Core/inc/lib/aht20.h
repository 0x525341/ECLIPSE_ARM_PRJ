/*
 * aht20.h
 *
 *  Created on: 31 авг. 2023 г.
 *      Author: r.sibgatullin
 */

#ifndef CORE_INC_LIB_AHT20_H_
#define CORE_INC_LIB_AHT20_H_

#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"
#include "delay.h"

#define AHT20_I2C_ADDRESS 0x38
#define AHT20_INIT_CMD 0xBE
#define AHT20_STATE_CMD 0x71
#define AHT20_START_MEASUREMENT_CMD 0xAC
#define AHT20_SOFT_RESET_CMD 0xBA

#ifndef TAHT_ONE_READ_DELAY_MS
#define TAHT_ONE_READ_DELAY_MS T_S(3)
#endif

#ifndef TAHT_ONE_MEASUREMENT_DELAY_MS
#define TAHT_ONE_MEASUREMENT_DELAY_MS  T_MS(80)
#endif

enum AHT_state
{
	START_MEASURENMENT,
	STOP_MEASURENMENT,
	READ_DATA,
	DELAY_NEXT_MEASUREMENT
};

typedef struct {
	uint8_t AHT_I2C_Addres;
	enum i2c_num I2C_num;
	enum AHT_state State;
} AHT_struct;

bool AHT20_Init(AHT_struct *AHT, enum i2c_num i2c, uint8_t AHT_I2C_address);
bool AHT20_StartMeasurement(AHT_struct *AHT);
bool AHT20_ReadData(AHT_struct *AHT, uint16_t *humidity, int16_t *temperature);
#endif /* CORE_INC_LIB_AHT20_H_ */
