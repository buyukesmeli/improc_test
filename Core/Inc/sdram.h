/*
 * sdram.h
 *
 *  Created on: 12 Eyl 2018
 *      Author: husein
 */

#ifndef SDRAM_H_
#define SDRAM_H_
#include <stdint.h>
#include "stm32f7xx_hal.h"
#include "fmc.h"

void SDRAM_Initialization_sequence(uint32_t RefreshCount);

#endif /* SDRAM_H_ */
