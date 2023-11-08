#include "stm32f103c8xx.h_gpio_driver.h"



/********************************************************
  * @fn                 - GPIO Peripheral clock controll
  *
  * @brief              - this func enable or disable peripheral clock for the given GPIO port
  *
  * @param [in]         - Base address of GPIO Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_PeriClockControll(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi){

    if(EnOrDi == ENABLE)
    {
      if(pGPIOx == GPIOA)
      {
          PA_PCLK_EN();
      }
      else if (pGPIOx == GPIOB)
      {
          PB_PCLK_EN();
      }
      else if (pGPIOx == GPIOC)
      {
          PC_PCLK_EN();
      }
      else if (pGPIOx == GPIOD)
      {
          PD_PCLK_EN();
      }
      else if (pGPIOx == GPIOE)
      {
          PE_PCLK_EN();
      }
      else if (pGPIOx == GPIOF)
      {
          PF_PCLK_EN();
      }
      else if (pGPIOx == GPIOG)
      {
          PG_PCLK_EN();
      }
    }
    else
    {
        
        //TODO
    }

}
/********************************************************
* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
//init de init  ########################################
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
    
    
    uint32_t temp1 = 0, temp2=0;
    //uint8_t pinNumber = 0;
        
    // configure the mode of GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_OUT_50mhz)
    {
        // Calculate the offset for the control registers (CRL or CRH)
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
    
        // Calculate the pin position within the control register
        temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8) * 4;
        
        // Clear the bits for the specific pin in the control register
        pGPIOHandle->pGPIOx->CR[temp1] &= ~(0xF << temp2);
        
        
         // Set the pin mode for the specific pin
        pGPIOHandle->pGPIOx->CR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << temp2);
        
        
        // Clear the bits for the specific pin in the control register
        //pGPIOHandle->pGPIOx->CR[temp1] &= ~(0x3 << temp2);
        
        
        pGPIOHandle->pGPIOx->CR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinConf << (2 + temp2));
     }
        else{
            
            
            if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
            {
                //1. configure the ftsr
                EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                // clear the correspnding bit
                EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                
            }else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
            {
                //1. configure the rtsr
                EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                // clear the correspnding bit
                EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            
            }else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
            {
                //1. configure both ftsr and rtsr
                EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                
                EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            }
            
            //configure GPIO port selection in AIFO
            uint8_t temp1, temp2, portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
            
            temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
            temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
            
            AIFO_PCLK_EN();
            AIFO->EXTR[temp1] = portcode <<(temp2 * 4);
           
            
            //3. enable the exti delivery using imr
            EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
        
    }

    
    //  configure the speed
    
    //  configure the PuPd Settings
    
    //  configure the Output type
    
    //  configure the alternate functionality


}

/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

      if(pGPIOx == GPIOA)
      {
          PA_REG_RESET();
      }
      else if (pGPIOx == GPIOB)
      {
          PB_REG_RESET();
      }
      else if (pGPIOx == GPIOC)
      {
          PC_REG_RESET();
      }
      else if (pGPIOx == GPIOD)
      {
          PD_REG_RESET();
      }
      else if (pGPIOx == GPIOE)
      {
          PE_REG_RESET();
      }
      else if (pGPIOx == GPIOF)
      {
          PF_REG_RESET();
      }
      else if (pGPIOx == GPIOG)
      {
          PG_REG_RESET();
      }



}


/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
//read Write ##########################################

/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
  *
********************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

  return value;
}
/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
    uint16_t value;
    value = (uint16_t)pGPIOx->IDR ;
  return value;
}
/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){

    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->ODR |= (1<<PinNumber);
    }
    else
    {
        pGPIOx->ODR &= ~(1<<PinNumber);
    }


}
/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value){

    pGPIOx->ODR = value;


}
/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

  pGPIOx->ODR ^= (1<<PinNumber);

}
/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
//IRQ conf and ISR Handling ########################################
void GPIO_IRQInterruptConf(uint8_t IRQNumber, uint8_t EnOrDi){
    
    if(EnOrDi == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            //programm ISER0 reg
            *NVIC_ISER0 |= (1 << IRQNumber);
        
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            //programm ISER1 reg
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            //programm ISER2 reg
            *NVIC_ISER2 |= (1 << (IRQNumber % 64 ));
        
        }
        
            
        
    }
    else
    {
        if(IRQNumber <= 31)
        {
            //programm ICER0 reg
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            //programm ICER1 reg
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            //programm ICER1 reg
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        
        }
    }
    



}

/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority){
        
    //because of Interrupt pr register is divided, each part is also divided and lower part is not usable
    //so we have to use higher part
    //for example 
    /*
    *   32 bit is 4 byte and in each 4 bite is 8 bit
    *   every 60 IPP register has same structure
    *   so in a register we can use 4 priority 
    *   first would be from 0-8, second 8-16, 16-24,24-32
    *   we have 60 priority register and each one can configure 4 priority
    *   priority configuration uses 4 bit from 8 bit.
    *   so we have to configure higher bits
    *   this you can see in "generic user gude" documentation
    */
    
    
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    
    
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
    



}
/********************************************************

* @fn
  *
  * @brief
  *
  * @param [in]
  * @param [in]
  * @param [in]
  *
  * @return 
  *
  * @note
********************************************************/
void GPIO_IRQHandling(uint8_t PinNumber){
    
    //clear the EXTI PR Register corresponding the pin number
    if(EXTI->PR & (1 << PinNumber))
    {
        //clear
        EXTI->PR |= (1 << PinNumber);
    }

}