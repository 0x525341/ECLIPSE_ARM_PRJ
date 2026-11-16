/*
 * hc595.c
 *
 *  Created on: 16 мая 2023 г.
 *      Author: ICuser
 */
#include "hc595.h"

void HC595_init(HC595_struct *hc595, enum port_name port, uint32_t RCLK_pin, uint32_t SRCLK_pin, uint32_t SER_pin, uint32_t bit_num, enum pin_pull pull)
{
	hc595->HC595_Port = port;
	hc595->HC595_RCLK_Pin = RCLK_pin;
	hc595->HC595_SER_Pin = SER_pin;
	hc595->HC595_SRCLK_Pin = SRCLK_pin;
	hc595->HC595_bit_num = bit_num;

	port_pin_init(port, RCLK_pin|SER_pin|SRCLK_pin, PIN_MODE_OUTPUT, PIN_TYPE_OUT_PUSHPULL, pull, PIN_SPEED_LOW, PIN_AF_NOT, PIN_RESET);
}

void HC595_WriteData(HC595_struct *hc595, uint32_t data)
{
	for (uint32_t i = 0; i < hc595->HC595_bit_num; i++)
	{
		if ((data>>i) & 0x1)
		{
			port_pin_set(hc595->HC595_Port, hc595->HC595_SER_Pin);
		}
		else {
			port_pin_reset(hc595->HC595_Port, hc595->HC595_SER_Pin);
		}
		port_pin_set(hc595->HC595_Port, hc595->HC595_SRCLK_Pin);
		port_pin_reset(hc595->HC595_Port, hc595->HC595_SRCLK_Pin);
	}
	port_pin_set(hc595->HC595_Port, hc595->HC595_RCLK_Pin);
	port_pin_reset(hc595->HC595_Port, hc595->HC595_RCLK_Pin);
}
