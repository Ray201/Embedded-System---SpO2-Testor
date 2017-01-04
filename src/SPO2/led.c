#include "led.h"

void init_LED_pins()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable clock to GPIOD
    
    for (int i=12; i<=15; i++)
    {
        GPIOD->MODER &= ~(0x3 << (2*i)); // clear the 2 bits corresponding to pin i
        GPIOD->MODER |= (1 << (2*i));    // set pin i to be general purpose output
    }
}

void LED_On(uint32_t i)
{
    GPIOD->BSRRL = 1 << (i+12);
}

void LED_Off(uint32_t i)
{
    GPIOD->BSRRH = 1 << (i+12);
}

void toggle_LED1 ()
{
    int static LED1=0;
    if(LED1==0){
        LED_On(1);
        LED1 = 1;
    }
    else if(LED1==1){
        LED_Off(1);
        LED1 = 0;
    }
}