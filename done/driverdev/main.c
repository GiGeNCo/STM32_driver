#include "stm32f103c8xx.h"
#include "stm32f103c8xx.h_gpio_driver.h"




void delay()
{
    uint64_t counter = 350000;
    while(counter--);
}
int main()
{

    GPIO_Handle_t GpioLed;
    GpioLed.pGPIOx = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_10mhz;  //1 in reference manual is output mode
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTCONF_PP; //2 in reference manual is push pull mode
    
    
    //GPIO_Handle_t GpioButton;
    //GpioButton.pGPIOx = GPIOB;
    //GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
    //GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    //GpioButton.GPIO_PinConfig.GPIO_PinINType = GPIO_INMODE_PUPD;
    
    
    
    
    GPIO_PeriClockControll(GPIOC,ENABLE); //enable is macro and value is 1
    //GPIO_PeriClockControll(GPIOB,ENABLE); //enable is macro and value is 1
    //GPIO_Init(&GpioButton);
    GPIO_Init(&GpioLed);
    
    while(1)
    {
        if(GPIO_ReadFromInputPin(GPIOB,GPIO_PIN_1) == 0)
        {
           
          GPIO_TogglePin(GPIOC,13);
          delay();
        }
        
    }
    
    
  //return 0;
}
