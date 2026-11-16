/*
 * hc595.h
 *
 *  Created on: 16 мая 2023 г.
 *      Author: ICuser
 */

#ifndef _HC595_H_
#define _HC595_H_

#include "stdint.h"
#include "stdbool.h"
#include "port.h"

typedef struct {
	uint32_t HC595_Port;	//Порт (GPIOA, GPIOB, etc)
	uint32_t HC595_RCLK_Pin;
	uint32_t HC595_SRCLK_Pin;
	uint32_t HC595_SER_Pin;
	uint32_t HC595_bit_num;
} HC595_struct;

extern void HC595_init(HC595_struct *hc595, enum port_name port, uint32_t RCLK_pin, uint32_t SRCLK_pin, uint32_t SER_pin, uint32_t bit_num, enum pin_pull pull);
extern void HC595_WriteData(HC595_struct *hc595, uint32_t data);
#endif /* _HC595_H_ */
