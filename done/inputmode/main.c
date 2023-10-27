#include "stm32f103c8xx.h"

void delay(uint64_t value)
{
    while(value--);
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
      
    
    GPIO_Handle_t gpioButton;
    
    gpioButton.pGPIOx = GPIOB;
    gpioButton.GPIO_PinConfig.GPIO_PinNumber = 11;
    gpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;      //11
    gpioButton.GPIO_PinConfig.GPIO_PinConf = 2;  //0
    
    GPIO_PeriClockControll(GPIOB,ENABLE);
    GPIO_Init(&gpioButton);
    
    
    while(1)
    {
        
        if(GPIO_ReadFromInputPin(GPIOB,GPIO_PIN_11) == 1)
        {
          //delay(200000);
          GPIO_TogglePin(GPIOC,GPIO_PIN_13);
        }
    }
    
}
