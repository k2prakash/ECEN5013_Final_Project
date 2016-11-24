/*
 * gpio.h
 *
 *  Created on: Oct 6, 2016
 *      Author: kprakash
 */
#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

#define PB_LCD_RS 		    (0)
#define PB_LCD_RW		    (1)
#define PB_LCD_EN		    (2)



#define DATA_OUT		0xFF
#define PORTB_DATA_OUT 0x00
#define LCD_ENABLE  (GPIOB_PDOR |= 0x04)
#define LCD_DISABLE (GPIOB_PDOR &= 0x03)

#define LCD_WRITE_CMD (GPIOB_PDOR &= 0x04)
#define LCD_READ_CMD ( GPIOB_PDOR = 0x02)
#define FUNCTION_SET 0x30
#define SP_FUNCTION_SET 0x38
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON 0x0f
#define LCD_ENTRY_MODE 0x06
#define LCD_CLEAR 0x01
#define ONE_MILL_SEC 3190
#define BUSY_CON 0x80



void gpio_init(void);
void set_pins_for_gpio();
void delay_ms(int multiplier);
void lcd_busy_wait();
void lcd_init_sequence();



#endif /* INCLUDES_GPIO_H_ */
