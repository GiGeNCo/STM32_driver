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

    uint32_t temp = 0, temp1 = 0, temp2=0;
    //uint8_t pinNumber = 0;
    
    // configure the mode of GPIO pin
    
    temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
    temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
    
    pGPIOHandle->pGPIOx->CR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<(4*temp2));
    
    
    
    pGPIOHandle->pGPIOx->CR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinConf <<(2+(4*temp2)));
    
    
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

  return 0;
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


  return 0;
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
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){



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
void GPIO_IRQConf(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi){



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



}