/*
 * LCD_OUT.h
 *
 *  Created on: 18 июл. 2023 г.
 *      Author: r.sibgatullin
 */

#ifndef CORE_INC_BOARD_LCD_OUT_H_
#define CORE_INC_BOARD_LCD_OUT_H_

#include "conf.h"
#include "stdint.h"
#include "stdbool.h"
#include "LCD_1602.h"
#include "delay.h"

enum LCD_PAGE
{
	PAGE_TIME,
	PAGE_TEMP,
	PAGE_HUM,
	PAGE_RADIO_STATION,
	PAGE_END,
	PAGE_SETUP_VOLUME,
	PAGE_SETUP_STATION_PLAY,
	PAGE_SETUP_STATION_STOP,
	PAGE_SETUP_TEMP_HUM,
	PAGE_END_SETUP,
};

enum LCD_STATE
{
LCD_WORK,
LCD_SETUP
};

#define DELAY_LCD_PAGE_MS T_S(3)

extern void LCD_print_page(LCD_struct *LCD, DATA_struct *DATA, enum LCD_PAGE page);
#endif /* CORE_INC_BOARD_LCD_OUT_H_ */
