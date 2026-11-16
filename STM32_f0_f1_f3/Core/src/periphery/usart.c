#include "usart.h"

void usart_init(enum usart_num usart, uint32_t baud,
		enum usart_length length, enum usart_parity parity,
		enum usart_stopbits stopbits, bool en_int)
{

	  LL_USART_InitTypeDef USART_InitStruct = {0};

	  USART_InitStruct.BaudRate = baud;
	  USART_InitStruct.DataWidth = length;
	  USART_InitStruct.StopBits = stopbits;
	  USART_InitStruct.Parity = parity;
	  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	  LL_USART_Init((USART_TypeDef*)usart, &USART_InitStruct);
	  LL_USART_DisableIT_CTS((USART_TypeDef*)usart);
	  LL_USART_ConfigAsyncMode((USART_TypeDef*)usart);

		if (en_int)
		{
			LL_USART_EnableIT_RXNE((USART_TypeDef*)usart);
		}
}

void usart_start(enum usart_num usart)
{
	LL_USART_Enable((USART_TypeDef*)usart);
}

void usart_stop(enum usart_num usart)
{
	LL_USART_Disable((USART_TypeDef*)usart);
}

bool usart_is_rcv_not_empty(enum usart_num usart)
{
	return (bool)(LL_USART_IsActiveFlag_RXNE((USART_TypeDef*)usart));
}

uint8_t usart_read(enum usart_num usart)
{
	return LL_USART_ReceiveData8((USART_TypeDef*)usart);
}

void usart_send(enum usart_num usart, uint8_t data)
{
//	while(!LL_USART_IsActiveFlag_BSY((USART_TypeDef*)usart);
	while (!LL_USART_IsActiveFlag_TXE((USART_TypeDef*)usart)) {};
	LL_USART_TransmitData8((USART_TypeDef*)usart, data);
}

void usart_sendstr(enum usart_num usart, char str1[])
{
	uint8_t n;
	for(n=0;str1[n]!='\0';n++)
		usart_send(usart, str1[n]);
}
