#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"

/* Defines */

/* Enumerations */
typedef void (*handler)(void);
/* Exported functions */
void SysTick_Handler(void);
extern void systick_init(uint32_t period_ms, handler func);

#endif
