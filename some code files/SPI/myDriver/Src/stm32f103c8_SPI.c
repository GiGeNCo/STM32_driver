#include "stm32f103c8_SPI.h"


/********************************************************
  * @fn                 - SPI Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t  EnOrDi)
{

    if(EnOrDi == ENABLE)
    {
      if(pSPIx == SPI1)
      {
          SPI1_PCLK_EN();
      }
      else if (pSPIx == SPI2)
      {
          SPI2_PCLK_EN();
      }
      else if (pSPIx == SPI3)
      {
          SPI3_PCLK_EN();
      }
    }
    else
    {
        
        //TODO
    }



}


/********************************************************
  * @fn                 - SPI Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    //configure SPI cr1 register
    uint32_t tempreg= 0;
    
    //configure device mode
    tempreg |= pSPIHandle->SPIConf.SPI_DevMode << 2;
    
    //configure bus config
    if(pSPIHandle->SPIConf.SPI_BusConf == SPI_BUS_FD)
    {
        //BIDIMODE should be cleared
        tempreg &= ~(1 << 15);
    }
    else if(pSPIHandle->SPIConf.SPI_BusConf == SPI_BUS_FD)
    {
        //BIDIMODE should be set
        tempreg |= (1 << 15);
    }
    else if(pSPIHandle->SPIConf.SPI_BusConf == SPI_BUS_SIMPLEX_RX)
    {
        //BIDI MODE should be cleared
        tempreg &= ~(1 << 15);
        //RXONLY mode should be set
        tempreg |= (1 << 10);
    }
    else if(pSPIHandle->SPIConf.SPI_BusConf == SPI_BUS_SIMPLEX_TX)
    {
        //BIDI MODE should be cleared
        //tempreg &= ~(1 << 15);
        //TXONLY mode should be set
        //tempreg |= (1 << 15);
    }
    
    //configure the SPI Serial clock speed (baud rate)
    tempreg |= pSPIHandle->SPIConf.SPI_SclkSpeed << 3;
    
    //configure the DFF
    tempreg |= pSPIHandle->SPIConf.SPI_DFF << 11;
    
    //configure the cpol
    tempreg |= pSPIHandle->SPIConf.SPI_CPOL << 1;
    
    //configure the chpa
    tempreg |= pSPIHandle->SPIConf.SPI_CHPA << 0;
    
    
    //write tempreg to SPICR1 Register
    pSPIHandle->pSPIx->CR1 = tempreg;




}



/********************************************************
  * @fn                 - SPI Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

    if(pSPIx == SPI1)
      {
          SPI1_PCLK_EN();
      }
      else if (pSPIx == SPI2)
      {
          SPI2_PCLK_EN();
      }
      else if (pSPIx == SPI3)
      {
          SPI3_PCLK_EN();
      }


}



/********************************************************
  * @fn                 - SPI Peripheral clock controll
  *
  * @brief              - 
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{




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
void SPI_IRQInterruptConf(uint8_t IRQNumber, uint8_t EnOrDi){
    




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
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority){
        




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
void SPI_IRQHandling(SPI_Handle_t *pHandle){
    
    

}