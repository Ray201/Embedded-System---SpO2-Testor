#ifndef __GUI_H
#define __GUI_H

#include "LCD.h"
#include "touch.h"

static char weight_char[2] = "50";
static char height_char[3] = "150";
static int weight = 50;
static int height = 150;









void GUI_Init(void);
void GUI_Result(void);
void GUI_touch_set(void);

#endif 

