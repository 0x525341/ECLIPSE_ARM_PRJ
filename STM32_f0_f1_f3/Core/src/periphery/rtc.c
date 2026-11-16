/*
 * rtc.c
 *
 *  Created on: 19 окт. 2023 г.
 *      Author: Tramp
 */
#include "rtc.h"
#include "delay.h"

void rtc_init(uint32_t AsynchPrescaler, uint32_t SynchPrescaler)
{
	  LL_RTC_InitTypeDef RTC_InitStruct = {0};

	  RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
	  RTC_InitStruct.AsynchPrescaler = AsynchPrescaler-1;//127max
	  RTC_InitStruct.SynchPrescaler = SynchPrescaler-1;//32767max
	  LL_RTC_Init(RTC, &RTC_InitStruct);
	  LL_RTC_SetAsynchPrescaler(RTC, AsynchPrescaler-1);
	  LL_RTC_SetSynchPrescaler(RTC, SynchPrescaler-1);
}

void rtc_time_init(uint8_t *Hours, uint8_t *Minutes, uint8_t *Seconds)
{
	LL_RTC_TimeTypeDef RTC_TimeInitStruct = {0};

	RTC_TimeInitStruct.Hours = *Hours;
	RTC_TimeInitStruct.Minutes = *Minutes;
	RTC_TimeInitStruct.Seconds = *Seconds;
	RTC_TimeInitStruct.TimeFormat = LL_RTC_TIME_FORMAT_AM_OR_24;

	LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &RTC_TimeInitStruct);
}

void rtc_get_time (uint8_t* Hours, uint8_t* Minutes, uint8_t* Seconds)
 {
	uint32_t time = get_time();
	LL_RTC_ClearFlag_RS(RTC);
	while (LL_RTC_IsActiveFlag_RS(RTC) != 1)
	{
		if	((get_time() - time) == 1)
			return;
	}
		*Hours = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC));
		*Minutes = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC));
		*Seconds = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetSecond(RTC));
		return;
}
