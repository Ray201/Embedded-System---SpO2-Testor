#include "lcd.h"
#include "delay.h"

/*引脚说明
**CS->PD7
**RS->PD11
**WR->PD5
**RD->PD4
**LCD _D[0~15]->FSMC_D15~FSMC_D0即PD14,PD15,PD0,PD1,PE7~PE15,PD8~PD10
*/
void LCD_LineConf(void)//**********************************************GPIO初始化
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		//GPIO_SetBits(GPIOD,GPIO_Pin_All);/////////////////////////////////////////////
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//(RS)
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);	   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//(CS) 
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
		
		/* ili9481 RST Pin config*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void LCD_FSMCConf(void)//**********************************************FSMC初始化
{
  	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;

  	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  	p.FSMC_AddressSetupTime = 5;
  	p.FSMC_AddressHoldTime = 0;
  	p.FSMC_DataSetupTime = 9;
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_A;
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
  	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void LCD_WriteReg(u8 Reg, u16 Value)//*********************************写REG
{
  	LCD_REG=Reg;
  	LCD_RAM=Value;
}

u16 LCD_ReadReg(u8 Reg)//**********************************************读REG
{
  	LCD_REG=Reg;
  	return (LCD_RAM);
}

void LCD_WriteRAM(u16 RGB_Code)//**************************************写RAM
{
  	LCD_RAM=RGB_Code;
}

u16 LCD_ReadRAM(void)//************************************************读RAM
{
  	LCD_REG=0x22; 
  	return LCD_RAM;
}
void ili9481_Reset(void)
{
	//GPIO_SetBits(GPIOD,GPIO_Pin_6);
	RST_HIGH();
	delay_ms(1);
	//GPIO_ResetBits(GPIOD,GPIO_Pin_6);
	RST_LOW();
	delay_ms(1);
	//GPIO_SetBits(GPIOD,GPIO_Pin_6);
	RST_HIGH();
	delay_ms(1);
}

u16 LCD_Init(void)//***********************id=0x1260***************************LCD初始化
{ 
 
   	LCD_LineConf();
  	LCD_FSMCConf();
  	delay_ms(5); 
	ili9481_Reset();
    u16 lcdid;
  	lcdid=LCD_ReadReg(0x00);
 
	    LCD_WriteReg(0x0000,0x0001);    delay_ms(50);
	    LCD_WriteReg(0x0003,0xA8A4);    delay_ms(50);   
	    LCD_WriteReg(0x000C,0x0000);    delay_ms(50);   
	    LCD_WriteReg(0x000D,0x080C);    delay_ms(50);   
	    LCD_WriteReg(0x000E,0x2B00);    delay_ms(50);   
	    LCD_WriteReg(0x001E,0x00B0);    delay_ms(50);   
	    LCD_WriteReg(0x0001,0x2B3F);    delay_ms(50);   
	    LCD_WriteReg(0x0002,0x0600);    delay_ms(50);
	    LCD_WriteReg(0x0010,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0011,0x6070);    delay_ms(50);   
	    LCD_WriteReg(0x0005,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0006,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0016,0xEF1C);    delay_ms(50);
	    LCD_WriteReg(0x0017,0x0003);    delay_ms(50);
	    LCD_WriteReg(0x0007,0x0133);    delay_ms(50);         
	    LCD_WriteReg(0x000B,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x000F,0x0000);    delay_ms(50);   
	    LCD_WriteReg(0x0041,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0042,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0048,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0049,0x013F);    delay_ms(50);
	    LCD_WriteReg(0x004A,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x004B,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0044,0xEF00);    delay_ms(50);
	    LCD_WriteReg(0x0045,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0046,0x013F);    delay_ms(50);
	    LCD_WriteReg(0x0030,0x0707);    delay_ms(50);
	    LCD_WriteReg(0x0031,0x0204);    delay_ms(50);
	    LCD_WriteReg(0x0032,0x0204);    delay_ms(50);
	    LCD_WriteReg(0x0033,0x0502);    delay_ms(50);
	    LCD_WriteReg(0x0034,0x0507);    delay_ms(50);
	    LCD_WriteReg(0x0035,0x0204);    delay_ms(50);
	    LCD_WriteReg(0x0036,0x0204);    delay_ms(50);
	    LCD_WriteReg(0x0037,0x0502);    delay_ms(50);
	    LCD_WriteReg(0x003A,0x0302);    delay_ms(50);
	    LCD_WriteReg(0x003B,0x0302);    delay_ms(50);
	    LCD_WriteReg(0x0023,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0024,0x0000);    delay_ms(50);
	    LCD_WriteReg(0x0025,0x8000);    delay_ms(50);
	    LCD_WriteReg(0x004f,0);        
	    LCD_WriteReg(0x004e,0);     
delay_ms(50);
//	LCD_WR_REG(0x0022);
	//LCD_REG=0x0022;
  
	
	LCD_Font(&Font16x24);
    return lcdid;
//	LCD_Mode(5);							 
}

void LCD_Font(sFONT *font)//*******************************************设置字体16*24 12*12 8*12 8*8
{
  	Efont=font;
}

void LCD_Cursor(u16 Xpos, u16 Ypos)//**********************************设置光标
{
  	LCD_WriteReg(0x004e, Xpos);
  	LCD_WriteReg(0x004f, Ypos);
}


void LCD_Window(u16 Xpos, u16 Ypos, u16 Height, u16 Width)//X,Y为窗口左下角座标,注意设置窗口后座标不要超出该范围
{
  	if(Xpos>=Height)LCD_WriteReg(0x50,(Xpos-Height+1));
  	else LCD_WriteReg(0x50,0);
  	LCD_WriteReg(0x51,Xpos);
  	if(Ypos>=Width)LCD_WriteReg(0x52,(Ypos-Width+1)); 
  	else LCD_WriteReg(0x52,0);
  	LCD_WriteReg(0x53,Ypos);
  	LCD_Cursor(Xpos,Ypos);
}


void LCD_Mode(u8 mode)//***********************************************设置刷屏模式
{
	switch(mode)//常用4(横屏)和7(竖屏)
	{
		case 1:LCD_WriteReg(0x03,0x00);break;//向左向上:←ㄉ
		case 2:LCD_WriteReg(0x03,0x01);break;//向上向左:↑ㄉ
		case 3:LCD_WriteReg(0x03,0x02);break;//向右向上:→ㄊ
		case 4:LCD_WriteReg(0x03,0x03);break;//向上向右:↑ㄊ
		case 5:LCD_WriteReg(0x03,0x08);break;//向左向下:←ㄌ
		case 6:LCD_WriteReg(0x03,0x09);break;//向下向左:↓ㄌ
		case 7:LCD_WriteReg(0x03,0x0a);break;//向右向下:→ㄋ
		case 8:LCD_WriteReg(0x03,0x0b);break;//向下向右:↓ㄋ
	}
}

void LCD_Clear(u16 Color)//********************************************清屏
{
  	u32 index=0;
 
  	LCD_Cursor(50, 50);
  	LCD_REG=0x22;//WriteRAM_Prepare 
  	for(index=0;index<76800;index++)LCD_RAM=Color;
}

void LCD_Point(u16 xpos, u16 ypos,u16 color)//*************************画点
{
	LCD_Cursor(xpos,ypos);
	LCD_REG=0x22;//WriteRAM_Prepare 
	LCD_RAM=color;
}

void LCD_Line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)//*************画线
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_Point(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}

void LCD_Rect(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)//*************设置区
{
	LCD_Line(x1,y1,x2,y1,color);
	LCD_Line(x1,y1,x1,y2,color);
	LCD_Line(x1,y2,x2,y2,color);
	LCD_Line(x2,y1,x2,y2,color);
}

void LCD_Circle(u16 Xpos, u16 Ypos, u16 Radius, u16 color)//***********画圆
{
  	s32  Dec;
  	u32  CurX;
  	u32  CurY;
	 
  	CurX=0;
  	CurY=Radius;   
  	Dec=3-(Radius<<1);
  	while(CurX<=CurY)
  	{
		LCD_Point(Xpos+CurX,Ypos+CurY,color);
		LCD_Point(Xpos+CurX,Ypos-CurY,color);
		LCD_Point(Xpos-CurX,Ypos+CurY,color);
		LCD_Point(Xpos-CurX,Ypos-CurY,color);
		LCD_Point(Xpos+CurY,Ypos+CurX,color);
		LCD_Point(Xpos+CurY,Ypos-CurX,color);
		LCD_Point(Xpos-CurY,Ypos+CurX,color);
		LCD_Point(Xpos-CurY,Ypos-CurX,color);
		if(Dec<0)Dec+=(CurX<<2)+6;
	    else
	    {
	      	Dec+=((CurX-CurY)<<2)+10;
	      	CurY--;
	    }
	    CurX++;
  	}
}


void LCD_Fill(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)//*************填充颜色
{          
	u16 i,j;
	u16 xlen=0;

	xlen=y2-y1+1;	   
	for(i=x1;i<=x2;i++)
	{
	 	LCD_Cursor(y1,i);
		LCD_REG=0x22;      	  
		for(j=0;j<xlen;j++)LCD_WriteRAM(color); 	  
	}						  	    
}  

void LCD_Char(u16 Xpos, u16 Ypos, u8 Ascii, u16 color)//***************显示字符
{
	const u16 *c;
  	u16 Xaddr=0;
    u16 Yaddr=0;
  	u32 index=0,i=0;
					 
  	Xaddr=Xpos;
    Yaddr=Ypos;
	c=&Efont->table[(Ascii-32)*Efont->Height]; 
 // 	LCD_Cursor(Xaddr, Yaddr);
  	for(index=0;index<Efont->Height;index++)
  	{
    //	LCD_REG=0x22;//WriteRAM_Prepare
    	for(i=0;i<Efont->Width;i++)
    	{
            LCD_Cursor(Xaddr, Yaddr);
            LCD_REG=0x22;
			if((((c[index]&((0x80<<((Efont->Width/12)*8))>>i))==0x00)&&(Efont->Width<=12))||(((c[index]&(0x1<<i))==0x00)&&(Efont->Width>12)))
                LCD_WriteRAM(WHITE);
      		else LCD_WriteRAM(color);
            Yaddr--;
    	}
    	Xaddr++;
        Yaddr=Ypos;
    	//LCD_Cursor(Xaddr, Yaddr);
  	}
}

void LCD_String(u16 xpos, u16 ypos, u8 *ptr, u16 color)//**************显示字符串
{
  	u16 refypos=LCD_WIDTH-ypos;
    u16 refxpos=LCD_WIDTH-xpos;

  	while((*ptr!=0)&(((refypos+1)&0xFFFF)>=Efont->Width))
  	{
    	LCD_Char(xpos,refypos,*ptr,color);
    	refypos-=Efont->Width;
    	ptr++;
  	}
}


u32 mypow(u8 m,u8 n)//*************************************************m^n函数
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}			 
	 
void LCD_Num(u16 x, u16 y, s32 num, u8 len, u16 color)//***************显示数字
{         	
	u8 t,temp;
	u8 enshow=0;
	t=0;
	if(num<0)
	{
		LCD_Char(y,LCD_WIDTH-x-(Efont->Width)*t,'-',color);
		num=-num;
		t++;
	}						   
	for(;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_Char(y,LCD_WIDTH-x-(Efont->Width)*t,' ',color);
				continue;
			}else enshow=1; 		 	 
		}
	 	LCD_Char(y,LCD_WIDTH-x-(Efont->Width)*t,temp+'0',color); 
	}
} 

