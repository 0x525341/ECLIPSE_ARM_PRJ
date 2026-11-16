#ifndef __USART_H__
#define __USART_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_ll_usart.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_ll_usart.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_ll_usart.h"
#endif

#define USART_1_HANDLER		void USART1_IRQHandler(void)
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
#define USART_2_HANDLER		void USART2_IRQHandler(void)
#define USART_3_HANDLER		void USART3_IRQHandler(void)
#endif

enum usart_num {
	USART_1 = (uint32_t)USART1,
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	USART_2 = (uint32_t)USART2,
	USART_3 = (uint32_t)USART3
#endif
};

enum usart_length {
	USART_LENGTH_8 = LL_USART_DATAWIDTH_8B,
	USART_LENGTH_9 = LL_USART_DATAWIDTH_9B
};

enum usart_parity {
	USART_PARITY_NONE = LL_USART_PARITY_NONE,
	USART_PARITY_EVEN = LL_USART_PARITY_EVEN,
	USART_PARITY_ODD = LL_USART_PARITY_ODD,
};

enum usart_stopbits {
	USART_STOPBITS_1 = LL_USART_STOPBITS_1,
	USART_STOPBITS_2 = LL_USART_STOPBITS_2,
#if defined ( STM32F103xE ) || defined ( STM32F103xB ) || defined ( STM32F373xC )
	USART_STOPBITS_0_5 = LL_USART_STOPBITS_0_5,
	USART_STOPBITS_1_5 = LL_USART_STOPBITS_1_5,
#endif
};

extern void usart_init(enum usart_num usart, uint32_t baud,
		enum usart_length length, enum usart_parity parity, enum usart_stopbits stopbits, bool en_int);
extern void usart_start(enum usart_num usart);
extern void usart_stop(enum usart_num usart);
extern uint8_t usart_read(enum usart_num usart);
extern void usart_send(enum usart_num usart, uint8_t data);
extern bool usart_is_rcv_not_empty(enum usart_num usart);
extern void usart_sendstr(enum usart_num usart, char str1[]);

#endif
