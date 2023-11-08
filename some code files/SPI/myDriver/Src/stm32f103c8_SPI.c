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

void SPI_DeInit(SPI_Handle_t *pSPIx)
{




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