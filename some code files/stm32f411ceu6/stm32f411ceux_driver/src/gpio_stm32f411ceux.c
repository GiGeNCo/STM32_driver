#include "stm32f411ceux.h"




/********************************************************
  * @fn                 - RCC_EN_GPIO
  *
  * @brief              - this func activate exact rcc on gpiox
  *
  * @param [in]         - pgpiox
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void RCC_EN_GPIO(GPIO_Reg *pgpiox)
{
    //enable clock for selected peripheral
    if(pgpiox == GPIOA)
    {
        RCC->RCC_AHB1ENR |= (1<<0);
    }
    else if(pgpiox == GPIOB)
    {
        RCC->RCC_AHB1ENR |= (1<<1);
    }
    else if(pgpiox == GPIOC)
    {
        RCC->RCC_AHB1ENR |= (1<<2);
    }
    else if(pgpiox == GPIOD)
    {
        RCC->RCC_AHB1ENR |= (1<<3);
    }
    else if(pgpiox == GPIOE)
    {
        RCC->RCC_AHB1ENR |= (1<<4);
    }
    else if(pgpiox == GPIOH)
    {
        RCC->RCC_AHB1ENR |= (1<<7);
    }   


}

/********************************************************
  * @fn                 - RCC_EN_GPIO
  *
  * @brief              - this func activate exact rcc on gpiox
  *
  * @param [in]         - pgpiox
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_Init(GPIO_Handle *pGPIO)
{
    RCC_EN_GPIO(pGPIO->pGPIOx);
    
    pGPIO->pGPIOx->GPIO_MODER &= ~(3 << 26);
    
    pGPIO->pGPIOx->GPIO_MODER |= (pGPIO->GPIO_Conf.IOMode << 26);
    
    


}

void GPIO_Write(GPIO_Reg *pGPIO, uint8_t pinNumber, uint8_t value)
{
    if(value == HIGH)
    {
        pGPIO->GPIO_ODR |= (1 << 13);
    }
    else 
    {
        pGPIO->GPIO_ODR &= ~(1 << 13);
    }


}