/*
 * gpio.h
 *
 *  Created on: Oct 6, 2016
 *      Author: kprakash
 */
#ifndef INCLUDES_LCD_H_
#define INCLUDES_LCD_H_

#include "stdint.h"
#include "delay.h"
#include "MKL25Z4.h"
#include "cbuffer.h"

#define PB_LCD_RS 		    (0)
#define PB_LCD_RW		    (1)
#define PB_LCD_EN		    (2)



#define DATA_OUT			(0x00FF)
#define DATA_IN		    	~(0x00FF)
#define PORTB_DATA_OUT 		(0x00)

#define LCD_ENABLE  		(GPIOB_PSOR = 0x04)
#define LCD_DISABLE 		(GPIOB_PCOR = 0x04)

//#define LCD_WRITE_CMD  	(GPIOB_PCOR = ((1<<PB_LCD_RW) | (1 << PB_LCD_RS)))

#define LCD_SET_CMD 		(GPIOB_PCOR = (1<<PB_LCD_RS))
#define LCD_SET_DATA 		(GPIOB_PSOR = (1<<PB_LCD_RS))
#define LCD_READ 			(GPIOB_PSOR = (1<<PB_LCD_RW))
#define LCD_WRITE 			(GPIOB_PCOR = (1<<PB_LCD_RW))



#define SP_FUNCTION_SET 	(GPIOD_PDOR = 0x30)
#define FUNCTION_SET 		(GPIOD_PDOR = 0x38)
#define LCD_DISPLAY_OFF 	(GPIOD_PDOR = 0x08)
#define LCD_DISPLAY_ON 		(GPIOD_PDOR = 0x0f)
#define LCD_ENTRY_MODE 		(GPIOD_PDOR = 0x06)
#define LCD_CLEAR_DISPLAY 	(GPIOD_PDOR = 0x01)


#define BUSY_CON 			(0x80)

#define LCD_ROW1_ADDRESS 	(0x80)
#define LCD_ROW3_ADDRESS 	(0x90)
#define LCD_ROW2_ADDRESS 	(0xC0)
#define LCD_ROW4_ADDRESS 	(0xD0)
#define LCD_CGRAM_START 	(0x40)
#define LCD_CGRAM_END 		(0x7F)
#define LCD_SET_ADDR(x)		(GPIOD_PDOR = x)
#define LCD_PUT_CH(x)		(GPIOD_PDOR = x)



void lcd_init(void);
void lcd_busy_wait();
void lcd_init_sequence();
void lcd_write_command();
void lcd_read_command();
void lcd_write_data();
void lcd_goto_addr(uint8_t addr);
void lcd_goto_xy(uint8_t row, uint8_t column);
void lcd_put_ch(uint8_t c);
void lcd_print_ch(uint8_t c);
void lcd_put_str(char * str);
void lcd_print_cbuff(cbuffer* buff);

#endif /* INCLUDES_LCD_H_ */
