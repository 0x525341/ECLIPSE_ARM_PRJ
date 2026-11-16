#ifndef __DELAY_H__
#define __DELAY_H__

#include "stdint.h"
#include "stdbool.h"
#include "udelay.h"
/* Defines */
#define SYSTICK_PERIOD_MS       1
/* Time to system timer ticks */
#define CLOCKS_PER_SEC		(1000U / SYSTICK_PERIOD_MS)
#define T_S(s)			(CLOCKS_PER_SEC * (s))
#define T_MS(ms)		(CLOCKS_PER_SEC / 1000 * (ms))
//#define T_US(us)		(CLOCKS_PER_SEC * (us) / 1000000)
#define T_MIN(min)		(T_S(60 * (min)))
/* Enumerations */

/* Exported functions */
extern uint32_t get_time(void);
extern void _delay_ms(uint32_t time_ms);
extern void _delay_handler(void);

#endif
