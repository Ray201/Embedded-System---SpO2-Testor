/*
** MAX30100 communication driver
** (c) mikroe, 2015
*/

#ifndef __MAX30100_DRIVER__
#define __MAX30100_DRIVER__

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "MAX30100_Defs.h"
#include "tm_stm32f4_i2c.h"

//#include <stdint.h>

// Getters
///////////

uint8_t MAX30100_Get( uint8_t anID );
uint8_t MAX30100_GetRevisionID();
uint8_t MAX30100_GetPartID();
uint8_t MAX30100_GetConfig();
uint8_t MAX30100_GetStatus();

// Setters
///////////

void MAX30100_SetConfig ( uint8_t cfg ); // desired config value
void MAX30100_SetInterrupt( uint8_t intrpts ); // desired interrupts
void MAX30100_Reset();
void MAX30100_Init();

// irBuff  - data from IR LED
// redBuff - data from red LED
uint8_t MAX30100_Read( uint16_t* irBuff, uint16_t* redBuff );

// tempValue - data from temperature sensor
void MAX30100_ReadTemp( uint16_t* tempValue );

#endif