/*
 * spi.h
 *
 *  Created on: Nov 5, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_
#include "stdint.h"
#include "MKL25Z4.h"
#include "stdlib.h"

#define SS_PIN				(0)

#define SS_SHIFT		(1 << SS_PIN)

#define SS_HIGH			(GPIOD_PSOR = SS_SHIFT)
#define SS_LOW		    (GPIOD_PCOR = SS_SHIFT)


void spi_init(void);
uint8_t spi_read();
uint8_t spi_write(uint8_t data);
void spi_flush();

size_t spi_read_n();
void spi_write_n(size_t data);

#endif /* INCLUDES_SPI_H_ */




