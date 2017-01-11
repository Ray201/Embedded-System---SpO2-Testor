#ifndef __GUI_H
#define __GUI_H

#include "LCD.h"
#include "touch.h"

static char weight_char[2] = "50";
static char height_char[3] = "150";
static int weight = 50;
static int height = 150;

static char HW_char[2];
static char SpO2_char[2] = "00";
static char HR_char[2] = "00";
static int SpO2_out = 0;
static int HR_out = 0;







void GUI_Init(void);
void GUI_Result(void);
void GUI_touch_set(void);

#endif 

