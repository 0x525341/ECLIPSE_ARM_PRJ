/*
 * IN12.h
 *
 *  Created on: 13 окт. 2023 г.
 *      Author: r.sibgatullin
 */

#ifndef CORE_INC_LIB_IN12_H_
#define CORE_INC_LIB_IN12_H_
#include "hc595.h"
#include "conf.h"

#define NUM0            0b1000000000000000
#define NUM1            0b0100000000000000
#define NUM2            0b0010000000000000
#define NUM3            0b0001000000000000
#define NUM4            0b0000100000000000
#define NUM5            0b0000010000000000
#define NUM6            0b0000001000000000
#define NUM7            0b0000000100000000
#define NUM8            0b0000000010000000
#define NUM9            0b0000000001000000
#define NUMT            0b0000000000100000
#define IN12_1          0b0000000000010000
#define IN12_2          0b0000000000001000
#define IN12_3          0b0000000000000100
#define IN12_4          0b0000000000000010




//volatile uint8_t IN12_data[IN12_NUMS];
extern void IN12_set_num(HC595_struct *hc595, uint8_t item, uint8_t num);
extern void IN12_get_time(uint8_t* IN12_set_data, uint8_t hours, uint8_t minutes);
extern void IN12_set_humidity_temp(uint8_t* IN12_set_data, int16_t humidity_temp);
extern void IN12_glitch_effect(void);
extern void IN12_transit_effect(uint8_t* IN12_set_data);
#endif /* CORE_INC_LIB_IN12_H_ */
