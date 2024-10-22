#include "i2c_stm32f411ceux.h"


/********************************************************
  * @fn                 - I2C Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of I2C Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void I2C_PeriClockControl(I2C_Reg_t *pI2Cx, uint8_t  EnOrDi)
{

    if(EnOrDi == ENABLE)
    {
      if(pI2Cx == I2C1)
      {
          I2C1_PCLK_EN();
      }
      else if (pI2Cx == I2C2)
      {
          I2C2_PCLK_EN();
      }
      else if (pI2Cx == I2C3)
      {
          I2C3_PCLK_EN();
      }
    }
    else
    {
        
        //TODO
    }



}


/********************************************************
  * @fn                 - I2C Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of I2C Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    


}



/********************************************************
  * @fn                 - I2C Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of I2C Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void I2C_DeInit(I2C_Reg_t *pI2Cx)
{

    if(pI2Cx == I2C1)
      {
          I2C1_PCLK_EN();
      }
      else if (pI2Cx == I2C2)
      {
          I2C2_PCLK_EN();
      }
      else if (pI2Cx == I2C3)
      {
          I2C3_PCLK_EN();
      }


}


uint8_t I2C_GetFlagStatus(I2C_Reg_t *pI2Cx, uint32_t FlagName)
{
    
    return 0;
}






/*
//other Peripheral API
void I2C_PeriControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pI2Cx->CR1 |= (1<<I2C_CR1_SPE);
    }
    else
    {
        pI2Cx->CR1 &= ~(1<<I2C_CR1_SPE);
    }


}

*/
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
void I2C_IRQInterruptConf(uint8_t IRQNumber, uint8_t EnOrDi){
    




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
void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority){
        




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
void I2C_IRQHandling(I2C_Handle_t *pHandle){
    
    

}

