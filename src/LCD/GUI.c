#include "GUI.h"

static int mode_flag = 0;

void GUI_Init(void)
{
  	LCD_Clear(LGRAYBLUE);
    
    LCD_String(15,20,"HEALTH TESTER",BLACK);
    
    LCD_String(40,20,"Weight:(kg)",BLACK);
    LCD_Fill(120, 65, 200, 95,BLACK);
    LCD_Fill(205, 65, 230, 95,BLACK);
    LCD_Fill(90, 65, 115, 95,BLACK);
    LCD_String(70,144,weight_char,LGRAYBLUE);
    LCD_String(70,210,"+",LGRAYBLUE);
    LCD_String(70,95,"-",LGRAYBLUE);
    
    LCD_String(95,20,"Height:(cm)",BLACK);
    LCD_Fill(120, 120, 200, 150,BLACK);
    LCD_Fill(205, 120, 230, 150,BLACK);
    LCD_Fill(90, 120, 115, 150,BLACK);
    LCD_String(125,136,height_char,LGRAYBLUE);
    LCD_String(125,210,"+",LGRAYBLUE);
    LCD_String(125,95,"-",LGRAYBLUE);
    
    LCD_Fill(105, 158, 135, 188,BLACK);
    LCD_Fill(185, 158, 215, 188,BLACK);
    LCD_String(165,110,"M",LGRAYBLUE);
    LCD_String(165,190,"F",LGRAYBLUE);

    
    LCD_Fill(20, 195, 120, 225,BLACK);
    LCD_Fill(200, 195, 300, 225,BLACK);
    LCD_String(200,210,"RESET",LGRAYBLUE);
    LCD_String(200,30,"START",LGRAYBLUE);

}

void HW_Eva(void)
{
    ;
}

void GUI_Result(void)
{
    LCD_Clear(LGRAYBLUE);
    LCD_String(10,20,"RESULT:",BLACK);
    LCD_String(40,40,"H-W Evaluation:",BLACK);
    
    LCD_String(65,40,HW_char,BLACK);
    
    LCD_String(95,40,"SpO2:",BLACK);
//    SpO2_out = SpO2;
    itoa(SpO2_out, SpO2_char, 10);
    LCD_String(120,40,SpO2_char,BLACK);
    
    LCD_String(150,40,"HeartRate:",BLACK);
//    HR_out = HR;
    itoa(HR_out, HR_char, 10);
    LCD_String(175,40,HR_char,BLACK);
    
    LCD_Fill(20, 195, 120, 225,BLACK);
    LCD_String(200,220,"MENU",LGRAYBLUE);
}



void GUI_func_Wmiun(void)
{
    LCD_String(70,95,"-",RED);
    weight = atoi(weight_char);
    weight --;
    itoa(weight, weight_char, 10);
    LCD_Fill(120, 65, 200, 95,BLACK);
    LCD_String(70,144,weight_char,LGRAYBLUE);
    
}

void GUI_func_Wplus(void)
{
    LCD_String(70,210,"+",RED);
    weight = atoi(weight_char);
    weight ++;
    itoa(weight, weight_char, 10);
    LCD_Fill(120, 65, 200, 95,BLACK);
    LCD_String(70,144,weight_char,LGRAYBLUE);

}

void GUI_func_Hmiun(void)
{
    LCD_String(125,95,"-",RED);
    height = atoi(height_char);
    height --;
    itoa(height, height_char, 10);
    LCD_Fill(120, 120, 200, 150,BLACK);
    LCD_String(125,136,height_char,LGRAYBLUE);
}

void GUI_func_Hplus(void)
{
    LCD_String(125,210,"+",RED);
    
    height = atoi(height_char);
    height ++;
    itoa(height, height_char, 10);
    LCD_Fill(120, 120, 200, 150,BLACK);
    LCD_String(125,136,height_char,LGRAYBLUE);
    
}

void GUI_func_Male(void)
{
    LCD_String(165,110,"M",YELLOW);
    LCD_String(165,190,"F",LGRAYBLUE);
    
}

void GUI_func_Female(void)
{
    LCD_String(165,110,"M",LGRAYBLUE);
    LCD_String(165,190,"F",YELLOW);
}

void GUI_func_Start(void)
{
    GUI_Result();
    mode_flag = 1;
}

void GUI_func_Reset(void)
{
    weight = 50;
    height = 150;
    itoa(weight, weight_char, 10);
    itoa(height, height_char, 10);
    GUI_Init();
    
}


const void (*func[8])(void) = {GUI_func_Wmiun, GUI_func_Wplus, GUI_func_Hmiun, GUI_func_Hplus, GUI_func_Male, GUI_func_Female, GUI_func_Start, GUI_func_Reset};

static int f_cond[8] = {0,0,0,0,0,0,0,0};

void Func_condition(void)
{
    int test_x=240-(Read_XY(CMD_RDX)-165)/7;
    int test_y=320-(Read_XY(CMD_RDY)-220)/5.3;
    f_cond[0] = (test_x >= 145) & (test_x <= 175) & (test_y <= 230) & (test_y >= 205);
    f_cond[1] = (test_x >= 145) & (test_x <= 175) & (test_y <= 115) & (test_y >= 90);
    f_cond[2] = (test_x >= 90) & (test_x <= 120) & (test_y <= 230) & (test_y >= 205);
    f_cond[3] = (test_x >= 90) & (test_x <= 120) & (test_y <= 115) & (test_y >= 90);
    f_cond[4] = (test_x >= 52) & (test_x <= 82) & (test_y <= 215) & (test_y >= 185);
    f_cond[5] = (test_x >= 52) & (test_x <= 82) & (test_y <= 135) & (test_y >= 105);
    f_cond[6] = (test_x >= 15) & (test_x <= 45) & (test_y <= 300) & (test_y >= 200);
    f_cond[7] = (test_x >= 15) & (test_x <= 45) & (test_y <= 120) & (test_y >= 20);
}

static int touch_flag = 0;
static int touch_counter = 0;


void GUI_touch_set(void)
{
    Func_condition();
    
    if(mode_flag==0)
    {
        
        int index = 0;
    
        for (index = 0; index < 8; index++)
        {
            if(f_cond[index])
            {
                if (touch_flag==index)
                {
                    if(touch_counter >= 10)
                    {
                        func[index]();
                        touch_counter = 0;
                    }
                    else touch_counter++;
                }
                else
                {
                    touch_flag = index;
                    touch_counter = 0;
                }
            }
        }
    }
    if(mode_flag==1)
    {
        if(f_cond[7])
        {
            
                if(touch_counter >= 10)
                {
                    func[7]();
                    touch_counter = 0;
                    mode_flag = 0;
                }
                else touch_counter++;

        }
    }
    
    
}



