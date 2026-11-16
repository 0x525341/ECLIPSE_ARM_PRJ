
#ifndef LCD_1602_H_
#define LCD_1602_H_

#define USE_PCF8574_MODULE
#include <stdint.h> //uint
#include "port.h"
#include <delay.h>

#ifdef USE_PCF8574_MODULE
#define PCF8575_I2C_ADDRES 0x27
#include "i2c.h"
#endif

//-------------------------------------------------------
//#define LCD_SCROLL_PERIOD_MS	    T_S(3)

#define LCD_STROBE_DELAY_US	        500

#define LCD_COMMAND			        0
#define LCD_DATA			        0x01

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit
//-------------------------------------------------------

typedef struct {
#ifndef USE_PCF8574_MODULE
	uint32_t LCD_CONTROL_Port;	//Порт (GPIOA, GPIOB, etc)
	uint32_t LCD_RS_Pin;
	uint32_t LCD_E_Pin;
	uint32_t LCD_DATA_Port;	//Порт (GPIOA, GPIOB, etc)
	uint32_t LCD_D4_Pin;
	uint32_t LCD_D5_Pin;
	uint32_t LCD_D6_Pin;
	uint32_t LCD_D7_Pin;
#else
	uint8_t LCD_I2C_Addres;
	enum i2c_num I2C_num;
	uint8_t LED_State;
#endif
} LCD_struct;

enum LCD_scroll_var
{
	LEFT = LCD_MOVELEFT,
	RIGHT = LCD_MOVERIGHT,
};
//-------------------------------------------------------
#ifndef USE_PCF8574_MODULE
extern void LCD_init(LCD_struct *LCD, enum port_name COMTROL_port, uint32_t RS_pin, uint32_t E_pin,
		enum port_name DATA_port, uint32_t D4_pin, uint32_t D5_pin, uint32_t D6_pin, uint32_t D7_pin);
#else
extern void LCD_init(LCD_struct *LCD, enum i2c_num i2c, uint8_t lcd_I2C_addres);
#endif
extern void LCD_print(LCD_struct *LCD, uint8_t byte);
extern void LCD_setcursor(LCD_struct *LCD, uint8_t str, uint8_t col);
extern void LCD_clear(LCD_struct *LCD);
extern void LCD_printstr(LCD_struct *LCD, char str1[]);
extern void LCD_set_led_state(LCD_struct *LCD, bool new_state);
extern void LCD_set_cursor_state(LCD_struct *LCD, bool cursor_state, bool cursor_blink_state);
extern void LCD_set_cursor_autoscroll_state(LCD_struct *LCD, bool cursor_autoscroll_state);
extern void LCD_add_custom_symbol(LCD_struct *LCD, uint8_t symbol_num, uint8_t *charmap);
extern void LCD_scroll(LCD_struct *LCD, enum LCD_scroll_var move);
extern void LCD_print_scroll_str(LCD_struct *LCD, char str1[], uint8_t str, uint8_t col, uint32_t perid_ms);
extern void LCD_print_scroll_str_2(LCD_struct *LCD, char str1[], uint8_t str, uint8_t col, uint8_t endcol, uint32_t perid_ms);


//-------------------------------------------------------
#endif /* LCD_1602_H_ */
