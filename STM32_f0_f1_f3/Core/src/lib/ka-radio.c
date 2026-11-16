/*
 * ka-radio.c
 *
 *  Created on: 15 окт. 2023 г.
 *      Author: Tramp
 */

#include "ka-radio.h"

#include "stdint.h"
#include "stdbool.h"
#include "usart.h"
#include "string.h"
#include "convert.h"
#include "rtc.h"

void karadio_parsing_data(DATA_struct *DATA, volatile char *radio_recieve_buffer)
{
	char command[7] = {};
	uint32_t command_len = 0;
	uint32_t data_len=0;

	if (!(radio_recieve_buffer[0]== '#' && radio_recieve_buffer[5] == '.'))
	return;

	for (uint32_t i = 0; radio_recieve_buffer[i+6] != COMMAND_POSTFIX; i++)
	{
		if (i==7) return;
		command[i] = radio_recieve_buffer[i+6];
		command_len++;
	}

	switch (command_len)
	{
	case 3:
		if((strncmp(command, VOL_VALUE, command_len))==0)
		{
			DATA->radio_volume = str_to_uint_convert(&radio_recieve_buffer[command_len+5+4]);
		}
		break;
	case 4:
		if((strncmp(command, TRACK_META, command_len))==0)
		{
			for (uint32_t i = (command_len+5+3); radio_recieve_buffer[i] != '\r'; i++)
			{
				DATA->radio_station_meta[data_len]=radio_recieve_buffer[i];
				data_len++;
			}
			DATA->radio_station_meta[data_len]='\0';
		}
		else if((strncmp(command, TIME_VAL, command_len))==0)
		{
			for (uint32_t i = 0; i<2; i++ )
			{
				DATA->radio_time_moth[ i ] = radio_recieve_buffer[i+18];
				DATA->radio_time_day[ i ] = radio_recieve_buffer[i+21];
				DATA->radio_time_hours[ i ] = radio_recieve_buffer[i+24];
				DATA->radio_time_minutes[ i ] = radio_recieve_buffer[i+27];
				DATA->radio_time_seconds[ i ] = radio_recieve_buffer[i+30];
			}
			DATA->radio_time_get_flag = true;
		}
	break;
	case 7:
		if((strncmp(command, STATION_NAME, command_len))==0)
		{
			for (uint32_t i = (command_len+5+3); radio_recieve_buffer[i] != '\r'; i++)
			{
				DATA->radio_station_name[data_len]=radio_recieve_buffer[i];
				data_len++;
			}
			DATA->radio_station_name[data_len]='\0';
		}
	break;
	}
}
