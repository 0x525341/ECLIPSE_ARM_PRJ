/*
 * main.c
 *
 *  Created on: 15 мая 2023 г.
 *      Author: ICuser
 */
#include "conf.h"
#include "cpu.h"
#include "rtc.h"
#include "clk.h"
#include "port.h"
#include "i2c.h"
#include "usart.h"
#include "adc.h"
#include "timer.h"
#include "nvic.h"
#include "systick.h"
#include "delay.h"
#include "exti.h"

static void cpu_board_ini(void)
{
//	cpu_clk_init(32000000, CPU_CLK_HSE, CPU_CLK_MUL_4, CPU_CLK_DIV_1, APB1_DIV_1);
	cpu_clk_init(32000000, CPU_CLK_HSE, CPU_CLK_MUL_4,CPU_CLK_DIV_1,APB1_DIV_1,APB2_DIV_1,CLK_ADC_DIV_2);
//	adc_clk_14RC_init();
	set_usart_clk_src(USART_CLK_SYSCLK);
	set_I2C_clk_src(I2C_CLK_SYSCLK);
	set_RTC_clk_src(RTC_CLK_HSE_DIV32);
}

static void usart_board_ini(void)
{
	clk_enable(CLK_USART1, APB1, GRP2);
	port_pin_init(USART_PORT, USART_TX_PIN|USART_RX_PIN, PIN_MODE_ALTER, PIN_TYPE_OUT_PUSHPULL, PIN_PULL_NOT, PIN_SPEED_HIGH, PIN_AF_1, PIN_RESET);
	usart_init(USART_1, 9600, USART_LENGTH_8, USART_PARITY_NONE, USART_STOPBITS_1, 1);
	usart_start(USART_1);
	nvic_set_priority(USART1_IRQn, 1);
	nvic_enable_irq(USART1_IRQn);
}

static void i2c_board_ini(void)
{
	clk_enable(CLK_I2C1, APB1, GRP1);
	port_pin_init(I2C_PORT, I2C_SDA_PIN|I2C_SCL_PIN, PIN_MODE_ALTER, PIN_TYPE_OUT_OPENDRAIN, PIN_PULL_NOT, PIN_SPEED_HIGH, PIN_AF_4, PIN_RESET);
	i2c_init(I2C_1, 0x00707CBB, 0);
	i2c_start(I2C_1);
}

void board_periphery_init(void)
{
	cpu_board_ini();
	clk_enable(CLK_PORTA, AHB1, GRP1);
	clk_enable(CLK_PORTB, AHB1, GRP1);
	usart_board_ini();
	i2c_board_ini();
	clk_enable(CLK_ADC1, APB1, GRP2);
	adc_x_init(ADC_1, ADC_CLK_SRC_ASYNC);
	adc_pin_init(PHOTO_PORT, PHOTO_PIN);
	port_pin_init(LED_PORT, LED_PIN, PIN_MODE_ALTER, PIN_TYPE_OUT_PUSHPULL, PIN_PULL_NOT, PIN_SPEED_LOW, PIN_AF_4, PIN_RESET);
	nvic_set_priority(SysTick_IRQn, 3);
	systick_init(SYSTICK_PERIOD_MS, _delay_handler);
	nvic_enable_irq(SysTick_IRQn);
	rtc_init(125, 2000);//1hz
}

//----------main----------
int main(void)
 {
	board_periphery_init();
	_delay_ms(1000);

	while (1) {}

}
