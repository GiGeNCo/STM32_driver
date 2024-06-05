#include "GPIO_STM32F103C8xx.h"

void Enable_RCC(GPIO_Registers *pGPIOx)
{
	if(GPIOA == pGPIOx)
        {
            RCC_EN_PA;
        }
        else if (pGPIOx == GPIOB)
        {
            RCC_EN_PB;
        }
        else if (pGPIOx == GPIOC)
        {
            RCC_EN_PC;
        }
        else if (pGPIOx == GPIOD)
        {
            RCC_EN_PD;
        }
        else if (pGPIOx == GPIOE)
        {
            RCC_EN_PE;
        }
        else if (pGPIOx == GPIOF)
        {
            RCC_EN_PF;
        }
        else if (pGPIOx == GPIOG)
        {
            RCC_EN_PG;
        }
}

void GPIO_Init(GPIO_Handler *pGPIO)
{
    uint8_t HorL = 0, regbit =0;
    
    HorL = pGPIO->GPIO_Configuration.GPIO_PinNumber / 8;
    regbit = (pGPIO->GPIO_Configuration.GPIO_PinNumber % 8) * 4;
    
    //clear our pin configuration
    pGPIO->pGPIOx->CR[HorL] &= ~(0x0f << regbit);
    
    //write our configuration into register
    pGPIO->pGPIOx->CR[HorL] |= (pGPIO->GPIO_Configuration.GPIO_Mode << regbit);
    pGPIO->pGPIOx->CR[HorL] |= (pGPIO->GPIO_Configuration.GPIO_Cfn << (regbit+2));


}

void GPIO_Write(GPIO_Registers *pGPIO, uint8_t pinNumber,uint8_t value )
{
    if(value == HIGH)
    {
        pGPIO->BSRR |= (1 << pinNumber);
    }
    else if(value == LOW)
    {
        pGPIO->BSRR |= (1 << (pinNumber+16));
    }
}
uint8_t GPIO_Read(GPIO_Registers *pGPIO, uint8_t pinNumber)
{
    if(((pGPIO->IDR >> 15) & 1) == HIGH)
    {        
        return 1;
    }
    else
    {
        return 0;
    }

}
