
#include "LCD_1602.h"


#include <udelay.h>
#include <stdlib.h>

//-------------------------------------------------------
static void LCD_sendhalfByte(LCD_struct *LCD, uint8_t byte)
{
#ifndef USE_PCF8574_MODULE
	port_pin_set(LCD->LCD_CONTROL_Port, LCD->LCD_E_Pin);
	_delay_us(LCD_STROBE_DELAY_US);
	
	port_pin_reset(LCD->LCD_DATA_Port, LCD->LCD_D4_Pin|LCD->LCD_D5_Pin|LCD->LCD_D6_Pin|LCD->LCD_D7_Pin);
	
	if (byte & (1<<3))
		port_pin_set(LCD->LCD_DATA_Port, LCD->LCD_D7_Pin);
	
	if (byte & (1<<2))
		port_pin_set(LCD->LCD_DATA_Port, LCD->LCD_D6_Pin);
	
	if (byte & (1<<1))
		port_pin_set(LCD->LCD_DATA_Port, LCD->LCD_D5_Pin);
	
	if (byte & (1<<0))
		port_pin_set(LCD->LCD_DATA_Port, LCD->LCD_D4_Pin);
	
	port_pin_reset(LCD->LCD_CONTROL_Port, LCD->LCD_E_Pin);
	_delay_us(LCD_STROBE_DELAY_US);
#else
	uint8_t temp = 0;
	temp = byte|En|LCD->LED_State;
	i2c_Write(LCD->I2C_num, LCD->LCD_I2C_Addres, &temp, 1, 100, MEDIUM);
	_delay_us(LCD_STROBE_DELAY_US);
	temp = byte|LCD->LED_State;
	i2c_Write(LCD->I2C_num, LCD->LCD_I2C_Addres, &temp, 1, 100, MEDIUM);
	_delay_us(LCD_STROBE_DELAY_US);
#endif
}
//-------------------------------------------------------
void LCD_sendByte(LCD_struct *LCD, uint8_t byte, uint8_t mode)
{
#ifndef USE_PCF8574_MODULE
	if (mode)
		port_pin_set(LCD->LCD_CONTROL_Port, LCD->LCD_RS_Pin);
	else
		port_pin_reset(LCD->LCD_CONTROL_Port, LCD->LCD_RS_Pin);
#endif
	LCD_sendhalfByte(LCD, ((byte&0xf0)|mode));
	LCD_sendhalfByte(LCD, (((byte<<4)&0xf0)|mode));
}

static void LCD_ini(LCD_struct *LCD)
{
	_delay_ms(15);
	LCD_sendhalfByte(LCD, 0x03 << 4);
	_delay_ms(4);
	LCD_sendhalfByte(LCD, 0x03 << 4);
	_delay_us(100);
	LCD_sendhalfByte(LCD, 0x03 << 4);
	_delay_ms(1);
	LCD_sendhalfByte(LCD, 0x02 << 4);
	_delay_ms(1);
	LCD_sendByte(LCD, LCD_FUNCTIONSET|LCD_2LINE|LCD_5x8DOTS|LCD_4BITMODE, LCD_COMMAND);
	_delay_ms(1);
	LCD_sendByte(LCD, LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSOROFF|LCD_BLINKOFF, LCD_COMMAND);
	_delay_ms(1);
	LCD_sendByte(LCD, LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT, LCD_COMMAND);
	_delay_ms(1);
}
//-------------------------------------------------------
#ifndef USE_PCF8574_MODULE
void LCD_init(LCD_struct *LCD, enum port_name COMTROL_port, uint32_t RS_pin, uint32_t E_pin,
		enum port_name DATA_port, uint32_t D4_pin, uint32_t D5_pin, uint32_t D6_pin, uint32_t D7_pin)
{
	LCD->LCD_CONTROL_Port = COMTROL_port;
	LCD->LCD_DATA_Port = DATA_port;
	LCD->LCD_E_Pin = E_pin;
	LCD->LCD_RS_Pin = RS_pin;
	LCD->LCD_D4_Pin = D4_pin;
	LCD->LCD_D5_Pin = D5_pin;
	LCD->LCD_D6_Pin = D6_pin;
	LCD->LCD_D7_Pin = D7_pin;

	port_pin_init(COMTROL_port, E_pin|RS_pin, PIN_MODE_OUTPUT, PIN_TYPE_OUT_PUSHPULL, PIN_PULL_NOT, PIN_SPEED_LOW, PIN_AF_NOT, PIN_RESET);
	port_pin_init(DATA_port, D4_pin|D5_pin|D6_pin|D7_pin, PIN_MODE_OUTPUT, PIN_TYPE_OUT_PUSHPULL, PIN_PULL_NOT, PIN_SPEED_LOW, PIN_AF_NOT, PIN_RESET);

	LCD_ini(LCD);
}
#else
void LCD_init(LCD_struct *LCD, enum i2c_num i2c, uint8_t lcd_I2C_addres)
{
	LCD->LCD_I2C_Addres = lcd_I2C_addres;
	LCD->I2C_num = i2c;
	LCD_ini(LCD);
}
#endif
//-------------------------------------------------------
void LCD_print(LCD_struct *LCD, uint8_t byte)
{
	LCD_sendByte(LCD, byte,LCD_DATA);
}
//-------------------------------------------------------
void LCD_setcursor(LCD_struct *LCD, uint8_t str, uint8_t col)
{
	uint8_t str_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	LCD_sendByte(LCD, (LCD_SETDDRAMADDR|(str_offsets[str]+col)), LCD_COMMAND);
}
//-------------------------------------------------------
void LCD_clear(LCD_struct *LCD)
{
	LCD_sendByte(LCD, LCD_CLEARDISPLAY, LCD_COMMAND);
	_delay_us(1500);
}
//-------------------------------------------------------
void LCD_printstr(LCD_struct *LCD, char str1[])
{
	uint8_t n;
	for(n=0;str1[n]!='\0';n++)
	LCD_print(LCD, str1[n]);
}

void LCD_print_scroll_str(LCD_struct *LCD, char str1[], uint8_t str, uint8_t col, uint32_t perid_ms)
 {
	static uint8_t step = 0;
	static uint32_t last_scroll_ms;

	if (get_time() - last_scroll_ms >= perid_ms) {

		uint8_t lin;
		for (lin = 0; str1[lin] != '\0'; lin++) {
		}
		int32_t count = (lin - 15) + col;
		if (count < 1) {
			LCD_setcursor(LCD, str, col);
			LCD_printstr(LCD, str1);
		} else {

			LCD_setcursor(LCD, str, col);

			if (step > count)
				step = 0;

			for (uint8_t t = col; t <= 15; t++) {
				LCD_print(LCD, str1[step + (t - col)]);
			}
			step++;
			last_scroll_ms = get_time();
		}
	}
}
//-------------------------------------------------------
void LCD_print_scroll_str_2(LCD_struct *LCD, char str1[], uint8_t str, uint8_t col, uint8_t endcol, uint32_t perid_ms)
 {
	static uint8_t step = 0;
	static uint32_t last_scroll_ms;

	if (get_time() - last_scroll_ms >= perid_ms) {

		uint8_t lin;
		for (lin = 0; str1[lin] != '\0'; lin++) {
		}
		int32_t count = (lin - endcol) + col;
		if (count < 1) {
			LCD_setcursor(LCD, str, col);
			LCD_printstr(LCD, str1);
		} else {

			LCD_setcursor(LCD, str, col);

			if (step > count)
				step = 0;

			for (uint8_t t = col; t <= endcol; t++) {
				LCD_print(LCD, str1[step + (t - col)]);
			}
			step++;
			last_scroll_ms = get_time();
		}
	}
}
//-------------------------------------------------------
void LCD_set_led_state(LCD_struct *LCD, bool new_state)
{
	if (new_state)
	{
		LCD->LED_State = LCD_BACKLIGHT;
	}
	else
	{
		LCD->LED_State = LCD_NOBACKLIGHT;
	}
}
//-------------------------------------------------------
void LCD_set_cursor_state(LCD_struct *LCD, bool cursor_state, bool cursor_blink_state)
{

	if(cursor_state)
	{
		if(cursor_blink_state)
		LCD_sendByte(LCD, LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSORON|LCD_BLINKON, LCD_COMMAND);
		else
		LCD_sendByte(LCD, LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSORON|LCD_BLINKOFF, LCD_COMMAND);
	}
	else
	{
		LCD_sendByte(LCD, LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSOROFF|LCD_BLINKOFF, LCD_COMMAND);
	}
}
//-------------------------------------------------------
void LCD_set_cursor_autoscroll_state(LCD_struct *LCD, bool cursor_autoscroll_state)
{

	if(cursor_autoscroll_state)
	{
		LCD_sendByte(LCD, LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTINCREMENT, LCD_COMMAND);
	}
	else
	{
		LCD_sendByte(LCD, LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT, LCD_COMMAND);
	}
}
//-------------------------------------------------------
void LCD_add_custom_symbol(LCD_struct *LCD, uint8_t symbol_num, uint8_t *charmap)
{
	uint8_t location = symbol_num & 0x7;// we only have 8 locations 0-7
	LCD_sendByte(LCD, LCD_SETCGRAMADDR | (location << 3), LCD_COMMAND);
	int i;
	for (i=0; i<8; i++) {
		LCD_print(LCD, charmap[i]);
	}
	//LCD_print(LCD, "\0-7"); print custom symbol
}
//-------------------------------------------------------
void LCD_scroll(LCD_struct *LCD, enum LCD_scroll_var move)
{
		LCD_sendByte(LCD, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | move, LCD_COMMAND);//max40 also to 0
}
