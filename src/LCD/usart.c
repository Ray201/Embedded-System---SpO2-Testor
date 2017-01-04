#include "usart.h"
#include "lcd.h"
#include <stdio.h>

u8 rn,dog=200,USART_RX_STA=0;//接收缓冲,4个字节.
u16	rm;
//初始化串口1
void COM1Init(u32 BaudRate)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
  
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART1);  
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART1);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    
  	USART_InitStructure.USART_BaudRate = BaudRate;//波特率设置
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能串口中断
  	USART_Init(USART2, &USART_InitStructure);
  	USART_Cmd(USART2, ENABLE);
  	//USART_ClearFlag(USART2, USART_FLAG_TC);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

}

void Uart2_Putchar(u8 ch)
{
	USART_SendData(USART2,(u8) ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}

void senddata(u8 sn,u16 sm)
{
	Uart2_Putchar(0xfe);
	Uart2_Putchar(sn);
	Uart2_Putchar(sm>>8);
	Uart2_Putchar(sm&0x00ff);
	Uart2_Putchar(sn);	
}

void USART2_IRQHandler(void)                	//串口1中断服务程序
	{
		static u8 USART_RX_BUF[4];
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
		{	 
			dog=200;//
			if(0Xfa==USART_ReceiveData(USART2)&USART_RX_STA==0)USART_RX_STA=1;
			else if (USART_RX_STA==1)
			{
				USART_RX_BUF[0]=USART_ReceiveData(USART2);
			    USART_RX_STA=2;// USART_SendData(USART2,USART_RX_BUF[0]);
			}
			else if (USART_RX_STA==2)
			{
				USART_RX_BUF[1]=USART_ReceiveData(USART2);
			  USART_RX_STA=3;	// USART_SendData(USART2,USART_RX_BUF[1]);
			}
			else if (USART_RX_STA==3)
			{
				USART_RX_BUF[2]=USART_ReceiveData(USART2);
			  USART_RX_STA=4;	//  USART_SendData(USART2,USART_RX_BUF[2]);
			}

			else if (USART_RX_STA==4)
			{
				USART_RX_BUF[3]=USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
				if(USART_RX_BUF[3]==USART_RX_BUF[0])
				 {
				 	
					 rn=USART_RX_BUF[0];
					 rm=(USART_RX_BUF[2]<<8)+USART_RX_BUF[1];
					 USART_RX_STA=5;
					 switch(rn)
					 {
							case 11://通风
							{
								USART_RX_STA=0;
							}break;
							default:break;
					 }
				}
				else
					USART_RX_STA=0;	//
		 }
		}
	}

#if 0
#pragma import(__use_no_semihosting)                              
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;         
_sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{
  	USART_SendData(USART1, (u8) ch);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  	return ch;
}
#endif
