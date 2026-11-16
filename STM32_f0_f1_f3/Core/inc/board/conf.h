/*
 * conf.h
 *
 *  Created on: 15 мая 2023 г.
 *      Author: ICuser
 */

#ifndef __CONF_H__
#define __CONF_H__

#include "port.h"
//----------PORT_CONFIG----------
#define DHT_PIN    		PIN_0
#define DHT_PORT   		PORT_A

#define PHOTO_PIN  		PIN_1
#define PHOTO_PORT 		PORT_A

#define SER_595_PIN  	PIN_4
#define SRCLK_595_PIN  	PIN_13
#define RCLK_595_PIN  	PIN_14
#define HC595_PORT 		PORT_A

#define ENC_A_PIN   	PIN_7
#define ENC_B_PIN   	PIN_6
#define ENC_BUTT_PIN  	PIN_5
#define ENC_PORT    	PORT_A

#define LED_PIN			PIN_1
#define LED_PORT		PORT_B

#define USART_TX_PIN 	PIN_2
#define USART_RX_PIN 	PIN_3
#define USART_PORT 		PORT_A

#define I2C_SCL_PIN		PIN_9
#define I2C_SDA_PIN		PIN_10
#define I2C_PORT		PORT_A
//----------PORT_CONFIG_END----------
#define IN12_UPDATE_HZ  		25
#define IN12_UPDATE_HANDLER 						void TIM17_IRQHandler(void)
#define ENCODER_CNT_UPDATE_HANDLER 		void TIM3_IRQHandler(void)
#define ENCODER_BUTTON_HANDLER      			void EXTI4_15_IRQHandler(void)
#define USART_RX_HANDLER      						void USART1_IRQHandler(void)
#define LED_UPDATE_HZ  		    250


enum IN12_STEP
{
	SNOW_TIME,
//	SNOW_TEMP,
//	SNOW_HUM,
//	SNOW_END,
};

typedef struct data
{
	uint8_t	hours;
	uint8_t	minutes;
	uint8_t	seconds;
	bool time_updated_flag;
	uint16_t humidity_home;
	uint16_t humidity_outside;
	int16_t	temp_home;
	int16_t	temp_outside;
	uint8_t radio_volume;
	uint8_t radio_station_num;
	bool radio_start;
	char radio_station_name[40];
	char radio_station_meta[40];
	char radio_time_hours[2];
	char radio_time_minutes[2];
	char radio_time_seconds[2];
	char radio_time_day[3];
	char radio_time_moth[3];
	bool radio_time_get_flag;
}DATA_struct;

#define LONG_PRESS_ENCODER_BUTTON_MS        T_S(2)
#define RADIO_VOLUME_MAX 254
#define SET_NEXT_STEP_LCD_PAGE_MS 			T_MIN(3)
#define UPDATE_TIME_DATA_IN12_MS 			T_S(1)

#define IN12_NUMS               4

#define IN12_TRANSIT_EFFECT_DELAY_MS        T_MS(500)
#define GLITCH_RANDE_TIME_MS 				T_S(30)
#define GLITCH_MIN_PERIOD_TIME_MS 			T_MIN(1)
#define UPDATE_LCD_MS				        T_MS(40)
#define UPDATE_LCD_MS				        T_MS(40)

#endif /* __CONF_H__ */
