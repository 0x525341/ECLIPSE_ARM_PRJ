#ifndef __UDELAY_H__
#define __UDELAY_H__

#include "stdint.h"
#include "cpu.h"

/* Defines */

#if (__CORTEX_M == 0 || __CORTEX_M == 1)
#	define __TIME_NCYCLES	4
#elif (__CORTEX_M == 3) || (__CORTEX_M == 4)
#	define __TIME_NCYCLES	3
#else
#	error "The unknown architecture"
#endif

#define UDELAY_LOOPS(us)	((uint32_t)((us) * (cpu_get_clk() / 1000000) / __TIME_NCYCLES))
#define _delay_us(us)		delay_n_cycles(UDELAY_LOOPS(us))

/* Exported functions */
static inline void delay_n_cycles(uint32_t loops) __attribute__((always_inline));
static inline void delay_n_cycles(uint32_t loops)
{
	asm volatile ("0:\n\t"
		      "sub	%0, #1\n\t"
		      "bne	0b"
		      : "=r" (loops) : "0" (loops) : "cc");
}
#endif
