/*
 * aht20.c
 *
 *  Created on: 31 авг. 2023 г.
 *      Author: r.sibgatullin
 */
#include "aht20.h"


bool AHT20_Init(AHT_struct *AHT, enum i2c_num i2c, uint8_t AHT_I2C_address)
{
	AHT->AHT_I2C_Addres = AHT_I2C_address;
	AHT->I2C_num = i2c;

	uint8_t init_cmd[] = {AHT20_INIT_CMD, 0x08, 0x00};

	return (i2c_Write(AHT->I2C_num, AHT->AHT_I2C_Addres, init_cmd, 3, 100, MEDIUM));
}

bool AHT20_StartMeasurement(AHT_struct *AHT)
{
	 uint8_t start_measurement_cmd[] = {AHT20_START_MEASUREMENT_CMD, 0x33, 0x00};
	 return (i2c_Write(AHT->I2C_num, AHT->AHT_I2C_Addres, start_measurement_cmd, 3, 100, MEDIUM));
}

bool AHT20_ReadData(AHT_struct *AHT, uint16_t *humidity, int16_t *temperature)
{
	static uint32_t TAHT_ONE_READ_MS;
	uint8_t data[6]= {0};
//	if (get_time() - TAHT_ONE_READ_DELAY_MS < TAHT_ONE_READ_DELAY_MS) return false;
//	else TAHT_ONE_READ_DELAY_MS = get_time();

	switch (AHT->State)
	{
	case START_MEASURENMENT:
		if(AHT20_StartMeasurement(AHT))
		 AHT->State = STOP_MEASURENMENT;
		TAHT_ONE_READ_MS = get_time();
		break;
	case STOP_MEASURENMENT:
		if (get_time() - TAHT_ONE_READ_MS < TAHT_ONE_MEASUREMENT_DELAY_MS)
			break;
		else AHT->State = READ_DATA;
		break;
	case READ_DATA:
		if(i2c_Read(AHT->I2C_num, AHT->AHT_I2C_Addres, data, 6, 100, MEDIUM))
			{
			*humidity = (uint16_t)(((((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4))*1000)>>20);
			*temperature = (int16_t)((((((uint32_t)(data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5])*2000)>>20)-500);
			AHT->State = DELAY_NEXT_MEASUREMENT;
			TAHT_ONE_READ_MS = get_time();
			return true;
			}
		break;
	case DELAY_NEXT_MEASUREMENT:
		if (get_time() - TAHT_ONE_READ_MS < TAHT_ONE_READ_DELAY_MS)
			break;
		else AHT->State = START_MEASURENMENT;
		break;
	}
return false;
}
