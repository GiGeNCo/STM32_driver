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
    
    //enable clock
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
    
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
    else if(pSPIHandle->SPIConf.SPI_BusConf == SPI_BUS_HD)
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
    
    tempreg |= pSPIHandle->SPIConf.SPI_CPOL << 1;
    //configure the cpol
    
    //configure the chpa
    tempreg |= pSPIHandle->SPIConf.SPI_CHPA << 0;
    
    

    tempreg |= pSPIHandle->SPIConf.SPI_SSM << 9;
    
    
    tempreg |= pSPIHandle->SPIConf.SPI_SSI << 8;
 
    
    
    //write tempreg to SPICR1 Register
    //pSPIHandle->pSPIx->CR1 = 0b0000001100000100;
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


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
    
    if(pSPIx->SR & FlagName)
    {
        return FLAG_SET;
    }
    else
    {
        return FLAG_RESET;

    }
}


/********************************************************
  * @fn                 - SPI Data Send
  *
  * @brief              - 
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - this is blocking call
********************************************************/

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while (Len > 0)
    {
        // 1 - wait until TX emprty is set
        //while( ! (pSPIx->SR & ( 1 << 1 )));
        uint8_t status = pSPIx->SR;
        while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG)==FLAG_RESET);
        // 2 - check dff bit in CR1
        
        
        if(pSPIx->CR1   & (1 << SPI_CR1_DFF))
        {
            // 16 bit mode
            // 1 - load the data into the DR
            pSPIx->DR = *((uint16_t*)pTxBuffer);
            Len--;
            Len--;
            //  ^^ up Len --; two times because we have just send out 2 bytes of data(16 bit)
            pTxBuffer++;
        }
        else 
        {
            // 8 bit mode
            // 1 - load the data into the DR
            //(*(volatile uint32_t*)(0x40013000 + 0x0C)) = *pTxBuffer;
            pSPIx->DR = *pTxBuffer;
            while (pSPIx->SR & 0x0080); // Wait until SPI is not busy
            Len--;
            pTxBuffer ++;
        }
        
    }


}


/********************************************************
  * @fn                 - SPI Receive Send
  *
  * @brief              - 
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - Enable or disable (macros 1 or 0)
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - this is blocking call
********************************************************/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    
}


//other Peripheral API
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1<<SPI_CR1_SPE);
    }
    else
    {
        pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
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
//IRQ conf and ISR Handling ########################################
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1<<SPI_CR1_SSI);
    }
    else
    {
        pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);
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

