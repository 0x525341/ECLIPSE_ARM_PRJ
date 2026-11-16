/*
 * LCD_OUT.c
 *
 *  Created on: 18 июл. 2023 г.
 *      Author: r.sibgatullin
 */

#include "LCD_OUT.h"
#include "convert.h"
#include "conf.h"


void LCD_print_page(LCD_struct *LCD, DATA_struct *DATA, enum LCD_PAGE page)
{
static uint32_t last_UPDATE_LCD_MS = 0;
if ((get_time() - last_UPDATE_LCD_MS) < UPDATE_LCD_MS)
{
	return;
}
char buffer[12]={0};
bool new_page_flag = false;

static enum LCD_PAGE old_page = PAGE_END;
if (page != old_page)
{
	LCD_clear(LCD);
 	old_page = page;
 	new_page_flag = true;
}

switch (page)
{
case PAGE_TIME:
	if (new_page_flag)
	{
	LCD_printstr(LCD, "TIME");
	LCD_setcursor(LCD, 0, 11);
	LCD_printstr(LCD, "DATA");

	LCD_setcursor(LCD, 1, 11);
	LCD_printstr(LCD, DATA->radio_time_day);
	LCD_print(LCD, '.');
	LCD_printstr(LCD, DATA->radio_time_moth);
	}

	Uint_to_str_convert(DATA->hours, &buffer[0], 10);
	LCD_setcursor(LCD, 1, 0);
	LCD_printstr(LCD, buffer);
	LCD_print(LCD, ':');
	Uint_to_str_convert(DATA->minutes, &buffer[0], 10);
	LCD_printstr(LCD, buffer);
	break;
case PAGE_TEMP:
	if (new_page_flag)
	{
	LCD_printstr(LCD, "HOME");
	LCD_setcursor(LCD, 0, 12);
	LCD_printstr(LCD, "OUTS");
	LCD_setcursor(LCD, 1, 6);
	LCD_printstr(LCD, "TEMP");
	}

	Int_to_str_convert((DATA->temp_home), &buffer[0], 10);
	LCD_setcursor(LCD, 1, 0);
	LCD_printstr(LCD, buffer);
	Int_to_str_convert((DATA->temp_outside), &buffer[0], 10);
	LCD_setcursor(LCD, 1, 12);
	LCD_printstr(LCD, buffer);
	break;
case PAGE_HUM:
	if (new_page_flag)
	{
	LCD_printstr(LCD, "HOME");
	LCD_setcursor(LCD, 0, 12);
	LCD_printstr(LCD, "OUTS");
	LCD_setcursor(LCD, 1, 6);
	LCD_printstr(LCD, "HUMI");
	}

	Uint_to_str_convert((DATA->humidity_home), &buffer[0], 10);
	LCD_setcursor(LCD, 1, 0);
	LCD_printstr(LCD, buffer);
	Uint_to_str_convert((DATA->humidity_outside), &buffer[0], 10);
	LCD_setcursor(LCD, 1, 12);
	LCD_printstr(LCD, buffer);
	break;
case PAGE_RADIO_STATION:
	if (new_page_flag)
	{
	LCD_print(LCD, '<');
//	LCD_setcursor(LCD, 0, 3);
//	LCD_printstr(LCD, "STATION");
	LCD_setcursor(LCD, 0, 15);
	LCD_print(LCD, '>');
	}

//	Uint_to_str_convert((DATA->radio_station_num), &buffer[0], 10);
//	LCD_setcursor(LCD, 0, 11);
//	LCD_printstr(LCD, buffer);
	LCD_print_scroll_str_2(LCD, DATA->radio_station_name, 0, 2, 13, T_MS(800));
	LCD_print_scroll_str(LCD, DATA->radio_station_meta, 1, 0, T_MS(450));
	break;
case PAGE_SETUP_VOLUME:
	if (new_page_flag)
	{
	LCD_setcursor(LCD, 0, 5);
	LCD_printstr(LCD, "VOLUME");
	}

	LCD_setcursor(LCD, 1, 0);
	for (uint32_t i = 0; i < (DATA->radio_volume/16); i++)
	{
		LCD_print(LCD, '>');
	}

	for (uint32_t i = 0; i < (15-(DATA->radio_volume/16)); i++)
	{
		LCD_print(LCD, ' ');
	}
	break;
case PAGE_SETUP_STATION_PLAY:
	if (new_page_flag)
	{
	LCD_setcursor(LCD, 0, 6);
	LCD_printstr(LCD, "PLAY");
	}
	break;
case PAGE_SETUP_STATION_STOP:
	if (new_page_flag)
	{
	LCD_setcursor(LCD, 0, 6);
	LCD_printstr(LCD, "STOP");
	}
	break;
}
}
