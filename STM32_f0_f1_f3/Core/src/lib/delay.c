#include "delay.h"

static volatile uint32_t current_time = 0;

/**
 * get_time() - get time in ms elapsed after start
 *
 * Return: current time in ms.
 */
uint32_t get_time(void)
{
	return current_time;
}

/**
 * delay_ms() - set delay time in ms
 *
 * Return: none.
 */
void _delay_ms(uint32_t time_ms)
{
	uint32_t end;

	end = get_time() + time_ms;
	while (end > get_time());
}

void _delay_handler(void)
{
	current_time++;
}
