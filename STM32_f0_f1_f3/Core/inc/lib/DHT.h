/*
 * DHT11.h
 *
 *  Created on: 26 янв. 2022 г.
 *      Author: r.sibgatullin
 */

#ifndef _DHT_H_
#define _DHT_H_

#include "stdint.h"
#include "stdbool.h"
#include "port.h"

#ifndef TDHT_ONE_DELAY_US
#define TDHT_ONE_DELAY_US 30
#endif

#ifndef TDHT_ONE_READ_DELAY_MS
#define TDHT_ONE_READ_DELAY_MS T_S(3)
#endif

typedef struct {
	uint32_t DHT_Port;	//Порт датчика (GPIOA, GPIOB, etc)
	uint32_t DHT_Pin;		//Номер пина датчика (GPIO_PIN_0, GPIO_PIN_1, etc)
	enum pin_pull pull;			//Нужна ли подтяжка линии данных к питанию (GPIO_NOPULL - нет, GPIO_PULLUP - да)
	bool DHT_calibrate;
} DHT_struct;

extern void DHT_init(DHT_struct *sensor, enum port_name port, uint32_t pin, enum pin_pull pull);
extern bool DHT11_ReadData(DHT_struct *sensor, uint8_t *temperature, uint8_t *humidity);
extern bool DHT22_ReadData(DHT_struct *sensor, int16_t *temperature, uint16_t *humidity);


#endif /* INC_DHT_H_ */
