/*
 * gpio.h
 *
 *  Created on: Oct 6, 2016
 *      Author: kprakash
 */
#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

#define PIN(x)			1 << x

#define LED_PIN			(9)

#define LED_SHIFT		(1 << LED_PIN)

#define LED_OFF			(GPIOC_PCOR |= LED_SHIFT)
#define LED_ON			(GPIOC_PSOR |= LED_SHIFT)

void gpio_init(void);

#endif /* INCLUDES_GPIO_H_ */
