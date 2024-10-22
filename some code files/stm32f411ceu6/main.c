#include "stm32f411ceux.h"


void delay(uint64_t value)
{
    while(value--);
}

int main()
{
    
    GPIO_Handle led;
    led.GPIO_Conf.IOMode = OUTPUT;
    led.GPIO_Conf.PinNumber = 13;
    led.pGPIOx = GPIOC;
    led.GPIO_Conf.Speed = LOWSPEED;
    led.GPIO_Conf.Type = PUSH_PULL;
    
    GPIO_Init(&led);
    
    while(1)
    {
        GPIO_Write(GPIOC,13,HIGH);
        delay(1000000);
        GPIO_Write(GPIOC,13,LOW);
        delay(1000000);
    }
}
