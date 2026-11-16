#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "stdint.h"
#include "stdbool.h"

#if defined ( STM32F103xE ) || defined ( STM32F103xB )
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_flash_ex.h"
#elif defined ( STM32F030x6 )
#include "stm32f0xx_hal_flash.h"
#include "stm32f0xx_hal_flash_ex.h"
#elif defined ( STM32F373xC )
#include "stm32f3xx_hal_flash.h"
#include "stm32f3xx_hal_flash_ex.h"
#endif

/* Defines */
#define EEPROM_BASE_ADDR FLASH_BASE

#define EEPROM_WORD_SIZE 4
#define EEPROM_PAGE_SIZE FLASH_PAGE_SIZE


#define EEPROM_ADDR(n, size) (EEPROM_BASE_ADDR + (n) * size)
#define EEPROM_PAGE_ADDR(n) (EEPROM_ADDR(n, EEPROM_PAGE_SIZE))
#define EEPROM_WORD_ADDR(n, page) \
		(EEPROM_PAGE_ADDR(page) + (n) * EEPROM_WORD_SIZE)

/* Enumerations */
/* Exported functions */
extern void eeprom_erase(void);
extern void eeprom_erase_page(uint32_t PageAddress);
extern uint32_t eeprom_read_word(uint32_t address);
extern void eeprom_program_word(uint32_t address, uint32_t data);

#endif
