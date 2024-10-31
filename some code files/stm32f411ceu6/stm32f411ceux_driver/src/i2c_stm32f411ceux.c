#include "i2c_stm32f411ceux.h"



uint16_t AHB_Prescaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_Prescaler[8] = {2,4,8,16};


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
  * @fn                 - get which clock is in use
  *
  * @brief              - 
  *
  * @param [in]         - 
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - IN RCC_CFGR register SWS (System clock switch status)
  *                       bit gvadzlevs statuss 
  *                       HSI, HSE, PLL tu romeli clock gamoiyeneba sistemashi
  *                     - also find prescaller
********************************************************/
uint32_t RCC_GetPLLOutputClock()
{

    return 0;
}

uint32_t RCC_GetPCLK1Value (void)
{   
    uint32_t pclk1, systemclock;
    
    uint8_t clkSrc, temp, ahbp,apb1p;
    
    clkSrc = (RCC->RCC_CFGR >> 2) & 3;
    
    if(clkSrc == 0)
    {
        systemclock = 16000000;
    }
    else if (clkSrc == 1)
    {
        systemclock = 8000000;
    }
    else if (clkSrc == 2)
    {
        systemclock = RCC_GetPLLOutputClock();
    }
    
    // for AHB
    temp = (RCC->RCC_CFGR >> 4) & 0xF;
    if(temp < 8)
    {
        ahbp = 1;
    }
    else
    {
        ahbp = AHB_Prescaler[temp-8];
    }
    
    // for Apb1
    temp = (RCC->RCC_CFGR >> 10) & 0x7;
    if(temp < 4)
    {
        apb1p = 1;
    }
    else
    {
        apb1p = APB1_Prescaler[temp-4];
    }
    pclk1 = (systemclock / ahbp) / apb1p;
    return pclk1;
}

/********************************************************
  * @fn                 - I2C Peripheral init func
  *
  * @brief              - 
  *
  * @param [in]         - I2C handler structure
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;
    
    //ack control bit
    tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10;
    pI2CHandle->pI2Cx->I2C_CR1 = tempreg;
    
    //comfigure freq field of CR2
    tempreg = 0;
    tempreg |= RCC_GetPCLK1Value() / 1000000U;
    //radganac 0-5 bitebi i2C_CR2 registrshi aris freq anu sixshiris
    //chavwert shemdegnairad:
    pI2CHandle->pI2Cx->I2C_CR2 = (tempreg & 0x3F); //0x3f aris 111111, 6 bit.
    
    //programm Device Own Address
    tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddr << 1;
    tempreg |= (1 << 14);
    pI2CHandle->pI2Cx->I2C_OAR1 = tempreg;
    
    //RCC calculation
    uint16_t ccr_value = 0;
    tempreg = 0;
    
    if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        //mode is standard mode
        ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
        tempreg = (ccr_value & 0xFFF);
    }
    else
    {
        //mode is fast mode    
        tempreg |= (1 << 15);
        tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
        if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value = (RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
        }
        else
        {        
            ccr_value = (RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
        }
        tempreg |= (ccr_value & 0xFFF);
    }
    pI2CHandle->pI2Cx->I2C_CRR = tempreg;
    
    


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

