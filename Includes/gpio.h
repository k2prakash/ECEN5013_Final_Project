/*
 * gpio.h
 *
 *  Created on: Oct 6, 2016
 *      Author: kprakash
 */
#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

#define PIN(x)			1 << x

#define RED				(18)
#define GREEN			(19)
#define BLUE			(1)

#define RED_SHIFT		(1 << RED)
#define GREEN_SHIFT		(1 << GREEN)
#define BLUE_SHIFT		(1 << BLUE)

#define RED_OFF			(GPIOB_PSOR = RED_SHIFT)
#define RED_ON			(GPIOB_PCOR = RED_SHIFT)
#define RED_TOGGLE   	(GPIOB_PTOR = RED_SHIFT)

#define GREEN_OFF		(GPIOB_PSOR = GREEN_SHIFT)
#define GREEN_ON		(GPIOB_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE   	(GPIOB_PTOR = GREEN_SHIFT)

#define BLUE_OFF		(GPIOD_PSOR = BLUE_SHIFT)
#define BLUE_ON			(GPIOD_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE   	(GPIOD_PTOR = BLUE_SHIFT)

void gpio_init(void);
void display_color(uint8_t color_code);
void set_pins_for_color();




#endif /* INCLUDES_GPIO_H_ */
