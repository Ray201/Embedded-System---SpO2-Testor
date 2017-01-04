#ifndef __USART_H
#define __USART_H

#include "stm32f4xx_conf.h"
extern u8 rn,dog,USART_RX_STA;         //接收状态标记	
extern u16	rm;
void uart_init(u32 bound);
void senddata(u8 sn,u16 sm);
void COM1Init(u32 BaudRate);

#endif

