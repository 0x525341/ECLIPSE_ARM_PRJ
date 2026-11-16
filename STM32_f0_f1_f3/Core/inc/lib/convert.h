/*
 * convert.h
 *
 *  Created on: 12 июл. 2023 г.
 *      Author: r.sibgatullin
 */

#ifndef CORE_INC_LIB_CONVERT_H_
#define CORE_INC_LIB_CONVERT_H_

#include "stdint.h"
#include "stdbool.h"

#endif /* CORE_INC_LIB_CONVERT_H_ */

extern void Uint_to_str_convert(uint32_t value, char *str, uint8_t radix);
extern void Int_to_str_convert(int32_t value, char *str, uint8_t radix);
extern int str_to_uint_convert(char *str);
