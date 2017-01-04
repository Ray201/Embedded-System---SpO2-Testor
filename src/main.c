#include "main.h"
#define SAMPLES 750

uint16_t temp_buffer[2000], spVal[2000];
uint16_t ir_buffer,red_buffer;
extern u8 reagent_name;
extern volatile uint32_t msTicks;
int last_call_t;



int main(void)
{
    // initialize STM32 system
    SystemInit();
    init_LED_pins();

    //initialize SPO2 sensor
    MAX30100_Init();

    //initialize LCD screen
	Touch_Init();
    u16 lcdid;
	lcdid=LCD_Init();
    GUI_Init();
    
    //state all the variable
    u16 test=100;
    
    
    uint32_t t_prev = 0;
    int l = 0;
    int i = 0;
    int j=1;
    char sample_num;
    
    uint16_t ir_buff[16]  = {0},
    red_buff[16] = {0};
    unsigned long ir_average,
    red_average;
    uint16_t buffer[2000];

    int touch_trigger=0;
    
    
	while(1)
	{

            GUI_touch_set();
        
        //sensor detection
        if (( MAX30100_GetStatus() & 0x20 ) != 0)
        {
            // Read IR and RED sensor data and store it in sampleNum
            sample_num = MAX30100_Read(ir_buff, red_buff);
            
            ir_average = ir_buff[0];
            red_average = red_buff[0];
            //get 750 samples
            ir_buffer = ir_average;
            red_buffer = red_average;
           
            //Whether there is a finger on sensor
            if(ir_buffer >30000 && ir_buffer<60000) // OGR = 750
            {
                spVal[j]+=((red_buffer*100)/ir_buffer);
                spVal[j]=118-((36*spVal[j])/100);
                buffer[j++] = ir_buffer;
            }
            
            if(j > SAMPLES) {j=0;}
        }
        
        //Heart beat toggle LED

            if(msTicks >= ((buffer[j-1]*1.5) + last_call_t)){
                toggle_LED1();          //operate function
                last_call_t=msTicks; //store current time to last call time
            }
    
        
        
        if ( (msTicks - t_prev) >= 1000 ) // every 1 ms
        {
            t_prev = msTicks;
        }
        
        
        

	}
}
