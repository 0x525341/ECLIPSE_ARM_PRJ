/*
 * rtc.h
 *
 *  Created on: 19 окт. 2023 г.
 *      Author: Tramp
 */

#ifndef CORE_INC_PERIPHERY_RTC_H_
#define CORE_INC_PERIPHERY_RTC_H_

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_rtc.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_rtc.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_rtc.h"
#endif

#include "stdint.h"
#include "stdbool.h"

extern void rtc_init(uint32_t AsynchPrescaler, uint32_t SynchPrescaler);
extern void rtc_time_init(uint8_t *Hours, uint8_t *Minutes, uint8_t *Seconds);
extern void rtc_get_time (uint8_t* Hours, uint8_t* Minutes, uint8_t* Seconds);
#endif /* CORE_INC_PERIPHERY_RTC_H_ */
