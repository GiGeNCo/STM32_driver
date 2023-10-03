#include "stm32f103c8xx.h"

void delay()
{
    uint32_t test = 0;
    for (uint64_t i = 0; i < 900000; i++) test--;
}
int main()
{

    GPIO_Handle_t gpioLed;
    
    gpioLed.pGPIOx = GPIOC;
    gpioLed.GPIO_PinConfig.GPIO_PinNumber = 13;
    gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2mhz;      //11
    gpioLed.GPIO_PinConfig.GPIO_PinConf = GPIO_OUTCONF_PP;          //0
    
    
    GPIO_PeriClockControll(GPIOC,ENABLE);
    GPIO_Init(&gpioLed);
    
    while(1)
    {
        GPIO_TogglePin(GPIOC,13);
        delay();
        
    }
    
}
