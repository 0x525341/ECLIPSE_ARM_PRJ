#include "eeprom.h"
void eeprom_erase(void)
{
	uint32_t PAGEError = 0;
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_MASSERASE;
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	  {
	    // error
	  }
	  HAL_FLASH_Lock();
}
void eeprom_erase_page(uint32_t address)
{
	uint32_t PAGEError = 0;
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = address;
	EraseInitStruct.NbPages = 0x01;
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	  {
		 while(1);//error
	  }
	  HAL_FLASH_Lock();
}

uint32_t eeprom_read_word(uint32_t address)
{
    return (*(__IO uint32_t*)address);
}

void eeprom_program_word(uint32_t address, uint32_t data)
{
	HAL_FLASH_Unlock();
	  if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) != HAL_OK)
			  {
			 while(1);//error
			  }
	  HAL_FLASH_Lock();
}
