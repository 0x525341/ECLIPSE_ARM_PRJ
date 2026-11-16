/*
 * IN12.c
 *
 *  Created on: 13 окт. 2023 г.
 *      Author: r.sibgatullin
 */

#include "IN12.h"
#include "hc595.h"
#include <stdlib.h>
#include "delay.h"
volatile uint8_t IN12_data[IN12_NUMS];

void IN12_set_num(HC595_struct *hc595, uint8_t item, uint8_t num)
{
	uint16_t IN12_item = 0;
	uint16_t IN12_num = 0;

	switch (item) {
	case 0:
		IN12_item = IN12_1;
		break;
	case 1:
		IN12_item = IN12_2;
		break;
	case 2:
		IN12_item = IN12_3;
		break;
	case 3:
		IN12_item = IN12_4;
		break;
	default:
		break;
	}
	switch (num) {
	case 0:
		IN12_num = NUM0;
		break;
	case 1:
		IN12_num = NUM1;
		break;
	case 2:
		IN12_num = NUM2;
		break;
	case 3:
		IN12_num = NUM3;
		break;
	case 4:
		IN12_num = NUM4;
		break;
	case 5:
		IN12_num = NUM5;
		break;
	case 6:
		IN12_num = NUM6;
		break;
	case 7:
		IN12_num = NUM7;
		break;
	case 8:
		IN12_num = NUM8;
		break;
	case 9:
		IN12_num = NUM9;
		break;
	case '.':
		IN12_num = NUMT;
		break;
	default:
		break;
	}

	HC595_WriteData(hc595 , IN12_item|IN12_num);
}

void IN12_get_time(uint8_t* IN12_set_data, uint8_t hours, uint8_t minutes)
{
	if (hours > 9)
	{
		IN12_set_data[0] = hours/10;
		IN12_set_data[1] = hours%10;
	}
	else
		{
		IN12_set_data[0] = 0xFF;
		IN12_set_data[1] = hours;
		}

	if (minutes > 9)
	{
		IN12_set_data[2] = minutes/10;
		IN12_set_data[3] = minutes%10;
	}
	else
		{
		IN12_set_data[2] = 0;
		IN12_set_data[3] = minutes;
		}
}

void IN12_set_humidity_temp(uint8_t* IN12_set_data, int16_t humidity_temp)
 {
	if (humidity_temp < 0) humidity_temp = humidity_temp * -1;

	uint8_t int_val = (uint8_t)(humidity_temp>>8);
	uint8_t fract_val = (uint8_t)(humidity_temp & 0xFF);

	if (int_val > 9) {
		{
			IN12_set_data[0] = int_val / 10;
			IN12_set_data[1] = int_val % 10;
		}
	} else {
		IN12_set_data[0] = 0xFF;
		IN12_set_data[1] = int_val;
	}

	if (fract_val > 9) {
		{
			IN12_set_data[2] = fract_val / 10;
			IN12_set_data[3] = fract_val % 10;
		}
	} else {
		IN12_set_data[2] = 0xFF;
		IN12_set_data[3] = fract_val;
	}
}

void IN12_glitch_effect(void)
{
static uint32_t last_IN12_glitch_TIME_MS;
	if (get_time() - last_IN12_glitch_TIME_MS
			>= (GLITCH_MIN_PERIOD_TIME_MS
					+ (uint32_t) (rand() % GLITCH_RANDE_TIME_MS))) {
		srand(get_time());
		uint8_t IN_num = (uint8_t) (rand() % IN12_NUMS);
		uint8_t num = (uint8_t) (rand() % 11);
		if (num == 10)
			num = 0xFF;
		uint8_t old_data = IN12_data[IN_num];

		for (uint32_t i = 0; i < (uint32_t) (rand() % 8); i++) {
			IN12_data[IN_num] = num;
			srand(get_time());
			_delay_ms((uint32_t) (rand() % 500));
			IN12_data[IN_num] = old_data;
			_delay_ms((uint32_t) (rand() % 250));
		}

		IN12_data[IN_num] = old_data;
		last_IN12_glitch_TIME_MS = get_time();
	}
}

void IN12_transit_effect(uint8_t* IN12_set_data)
{
	for(uint32_t count = 0; count < IN12_NUMS; count++)
	{
		if(IN12_set_data[count] != IN12_data[count])
		{
			while (IN12_data[count] != 9)
			{
				IN12_data[count] = IN12_data[count] + 1;
				_delay_ms(IN12_TRANSIT_EFFECT_DELAY_MS);
			}

			for (uint8_t i = 0; i < IN12_set_data[count]; i++)
			{
				IN12_data[count] = i;
				_delay_ms(IN12_TRANSIT_EFFECT_DELAY_MS);
			}

			IN12_data[count] = IN12_set_data[count];
		}
	}

}
