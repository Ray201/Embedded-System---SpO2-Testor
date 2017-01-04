#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_conf.h"


void init_LED_pins(void);
void LED_On(uint32_t i);
void LED_Off(uint32_t i);
void toggle_LED1();

#endif 

