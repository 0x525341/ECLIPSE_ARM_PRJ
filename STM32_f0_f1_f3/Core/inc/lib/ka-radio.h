/*
 * ka-radio.h
 *
 *  Created on: 15 окт. 2023 г.
 *      Author: Tramp
 */

#ifndef CORE_INC_LIB_KA_RADIO_H_
#define CORE_INC_LIB_KA_RADIO_H_

#include "conf.h"

#define VOL_GET         "cli.vo\r\n"
#define VOL_SET(x)  	"cli.vol("x")"
#define VOL_MINUS 		"cli.vol-\r\n"
#define VOL_PLUS   		"cli.vol+\r\n"
#define STATION_NEXT    "cli.next\r\n"
#define STATION_PREV    "cli.prev\r\n"
#define STATION_STOP    "cli.stop\r\n"
#define STATION_START   "cli.start\r\n"
#define STATION_GET_NUM "cli.start\r\n"
#define GET_TIME        "sys.date\r\n"

#define radio_recieve_buffer_size 100
//volatile char radio_recieve_buffer_1[radio_recieve_buffer_size];
//volatile char radio_recieve_buffer_2[radio_recieve_buffer_size];

#define  COMMAND_PREFIX    	"##CLI."
#define  VOL_VALUE        	"VOL"
#define  TRACK_META       	"META"
#define  TIME_VAL         	"DATE"
#define  STATION_NAME 	  	"NAMESET"
#define  COMMAND_POSTFIX   	'#'
#define  COMMAND_END   		':'
#define  PACKET_END   		'\n'

extern void karadio_parsing_data(DATA_struct *DATA, volatile char *radio_recieve_buffer);
#endif /* CORE_INC_LIB_KA_RADIO_H_ */
