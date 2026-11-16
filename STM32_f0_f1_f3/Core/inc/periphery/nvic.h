#ifndef __NVIC_H__
#define __NVIC_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx.h"
#endif

#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
/* Defines */

/* Enumerations */

/* Exported functions */
extern void nvic_enable_irq(IRQn_Type irq);
extern void nvic_disable_irq(IRQn_Type irq);
extern void nvic_clear_pending_irq(IRQn_Type irq);
extern void nvic_disable_irqs(void);
extern void nvic_enable_irqs(void);
extern void nvic_set_priority_grouping(uint32_t group);
extern void nvic_set_priority(IRQn_Type irq, uint32_t priority);

#endif
