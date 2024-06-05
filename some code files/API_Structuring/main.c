#include "stm32f103c8xx.h"

void delay(uint64_t value)
{
    while(value--);
}

int main()
{
    GPIO_Handler pin;
    pin.pGPIOx = GPIOC;
    pin.GPIO_Configuration.GPIO_PinNumber = 14;
    pin.GPIO_Configuration.GPIO_Mode    = OUTPUT_2MHZ;
    pin.GPIO_Configuration.GPIO_Cfn     = GPIO_OUT_PUSH_PULL;
      
    Enable_RCC(GPIOC);
    GPIO_Init(&pin);
    
    GPIO_Handler btnPin;
    
    btnPin.pGPIOx = GPIOC;
    btnPin.GPIO_Configuration.GPIO_PinNumber = 15;
    btnPin.GPIO_Configuration.GPIO_Mode = INPUT;
    btnPin.GPIO_Configuration.GPIO_Cfn = GPIO_IN_PULL_UP_PULL_DOWN;
    
    GPIO_Init(&btnPin);
    
    GPIO_Write(btnPin.pGPIOx,15,HIGH);
    
    while(1)
    {
        //GPIO_Write(pin.pGPIOx,14,HIGH);
        //delay(1000000);
        //GPIO_Write(pin.pGPIOx,14,LOW);
        //delay(1000000);
        if(GPIO_Read(btnPin.pGPIOx,15) == LOW)
        {
            GPIO_Write(pin.pGPIOx,14,HIGH);
        }
        else if(GPIO_Read(btnPin.pGPIOx,15) == HIGH)
        {
            GPIO_Write(pin.pGPIOx,14,LOW);
        }
        
        
    }
}
