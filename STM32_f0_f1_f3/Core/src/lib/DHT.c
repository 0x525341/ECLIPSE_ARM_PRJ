/*
 * DHT.c
 *
 *  Created on: 16 мая 2023 г.
 *      Author: ICuser
 */

#include "DHT.h"
#include "delay.h"

void DHT_init(DHT_struct *sensor, enum port_name port, uint32_t pin, enum pin_pull pull)
{
	sensor->DHT_Port = port;
	sensor->DHT_Pin = pin;
	sensor->pull = pull;
}

static void DHT_pin_to_out(DHT_struct *sensor)
{
	port_pin_init(sensor->DHT_Port, sensor->DHT_Pin, PIN_MODE_OUTPUT, PIN_TYPE_OUT_PUSHPULL, sensor->pull, PIN_SPEED_LOW, PIN_AF_NOT, PIN_RESET);
}

static void DHT_pin_to_in(DHT_struct *sensor)
{
	port_pin_init(sensor->DHT_Port, sensor->DHT_Pin, PIN_MODE_INPUT, PIN_TYPE_IN, sensor->pull, PIN_SPEED_LOW, PIN_AF_NOT, PIN_RESET);
}

static void DHT_PinChangeWait(DHT_struct *sensor, uint8_t currentState) {
  uint8_t counter = 0;
  while ((!port_pin_is_set(sensor->DHT_Port, sensor->DHT_Pin)) != currentState && ++counter < 255) {
	  _delay_us(1);
  }
}

static uint8_t DHT_ReadRawData(DHT_struct *sensor, uint8_t *raw_data_buffer) {
  DHT_pin_to_out(sensor);
  port_pin_reset(sensor->DHT_Port, sensor->DHT_Pin);

  _delay_ms(20);

  port_pin_set(sensor->DHT_Port, sensor->DHT_Pin);
  DHT_pin_to_in(sensor);

  DHT_PinChangeWait(sensor, PIN_SET);
  DHT_PinChangeWait(sensor, PIN_RESET);
  DHT_PinChangeWait(sensor, PIN_SET);

  for (uint8_t i = 0; i < 5; i++) {
    for (uint8_t j = 0; j < 8; j++) {
    	DHT_PinChangeWait(sensor, PIN_RESET);
      raw_data_buffer[i] <<= 1;
      _delay_us(TDHT_ONE_DELAY_US);
          if (port_pin_is_set(sensor->DHT_Port, sensor->DHT_Pin)) {
            raw_data_buffer[i] |= 1;
            DHT_PinChangeWait(sensor, PIN_SET);
          }
    }
  }

  return (raw_data_buffer[4] == (uint8_t) (raw_data_buffer[0] + raw_data_buffer[1] + raw_data_buffer[2] + raw_data_buffer[3]));
}

bool DHT11_ReadData(DHT_struct *sensor, uint8_t *temperature, uint8_t *humidity) {
  uint8_t raw_data[5] = {0, 0, 0, 0, 0};
    if (DHT_ReadRawData(sensor, raw_data)) {
      *temperature = (uint8_t) raw_data[2];
      *humidity = (uint8_t) raw_data[0];
      return true;
    }
  return false;
}

bool DHT22_ReadData(DHT_struct *sensor, int16_t *temperature, uint16_t *humidity) {
	static uint32_t TDHT_ONE_READ_PREV_MS;

	if (get_time() - TDHT_ONE_READ_PREV_MS < TDHT_ONE_READ_DELAY_MS) return 0;
	else TDHT_ONE_READ_PREV_MS = get_time();

  uint8_t raw_data[5] = {0, 0, 0, 0, 0};
    if (DHT_ReadRawData(sensor, raw_data)) {
    	if (raw_data[2] & 0x80)
    	{
    		raw_data[2] = raw_data[2] & 0x7F;
    	     *temperature = (((int16_t) raw_data[2] << 8) | raw_data[3]) * -1 ;
    	}
    	else {
    	      *temperature = ((int16_t) raw_data[2] << 8) | raw_data[3];
    	}
      *humidity = ((uint16_t) raw_data[0] << 8) | raw_data[1];
      return true;
    }
  return false;
}
