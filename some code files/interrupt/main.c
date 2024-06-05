#include "stm32f103c8xx.h"
#include "string.h"

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW


void delay(uint64_t value)
{
    while(value--);
}
int main()
{
    
   
    GPIO_Handle_t gpioLed;
    memset(&gpioLed,0,sizeof(gpioLed));
    GPIO_Handle_t gpioButton;
    memset(&gpioButton,0,sizeof(gpioButton));
    
    
    gpioLed.pGPIOx = GPIOC;
    gpioLed.GPIO_PinConfig.GPIO_PinNumber = 15;
    gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2mhz;      //11
    gpioLed.GPIO_PinConfig.GPIO_PinConf = GPIO_OUTCONF_PP;          //0
    
    GPIO_PeriClockControll(GPIOC,ENABLE);
    GPIO_Init(&gpioLed);
      
    

    
    gpioButton.pGPIOx = GPIOC;
    gpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
    gpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;      //11
    gpioButton.GPIO_PinConfig.GPIO_PinConf = GPIO_INMODE_PUPD;  //0
    
    GPIO_PeriClockControll(GPIOC,ENABLE);
    GPIO_Init(&gpioButton);
    
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10,15);
    GPIO_IRQInterruptConf(IRQ_NO_EXTI15_10,ENABLE);
      
  
    
    while(1)
    {
        
        
        //if(GPIO_ReadFromInputPin(GPIOB,GPIO_PIN_1) == HIGH)
        {
          //delay(20000);
          GPIO_TogglePin(GPIOC,GPIO_PIN_13);

        }


    }
    
}


void EXTI0_IRQHandler(void)
{
    //handle the interrupt
    GPIO_IRQHandling(0);

}
void EXTI15_10_IRQHandler(void)
{
    delay(20000);
    GPIO_IRQHandling(GPIO_PIN_12);
    GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    delay(20000);
    GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    delay(20000);
    GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    delay(20000);
}
