#include "SPI_STM32F103C8xx.h"

/********************************************************
  * @fn                 - SPI Peripheral clock controll
  *
  * @brief              - Enable clock for prefered SPI
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void RCC_ENABLE_SPI(SPI_Registers *pSPIx)
{
    if(pSPIx == SPI1)
    {
        RCC->APB2ENR |= (1 << 12);
    }
    else if (pSPIx == SPI2)
    {
        RCC->APB1ENR |= (1 << 14);
    }
    else if (pSPIx == SPI3)
    {
        RCC->APB1ENR |= (1 << 15);
    }
}


/********************************************************
  * @fn                 - SPI Peripheral Initialize
  *
  * @brief              - Initialize SPI registers
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void SPI_Init(SPI_Handler *pSPI)
{
    uint32_t tempreg = 0;
    
    
    tempreg |= pSPI->SPIConf.SPI_CHPA << 0;
    tempreg |= pSPI->SPIConf.SPI_CPOL << 1;
    tempreg |= pSPI->SPIConf.SPI_Mode << 2;
    tempreg |= pSPI->SPIConf.SPI_Speed << 3;
    tempreg |= pSPI->SPIConf.SPI_SSM << 9;
    tempreg |= pSPI->SPIConf.SPI_SSI << 8;
    tempreg |= pSPI->SPIConf.SPI_DFF << 11;
    
    pSPI->pSPIx->SPI_CR1 = tempreg;     //write our configuration into SPI CR1
    pSPI->pSPIx->SPI_CR1 |= (1<<6);     //Enable SPI on SPI_CR1
    
}

/********************************************************
  * @fn                 - SPI Peripheral Send data
  *
  * @brief              - transmit data using SPI
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - data
  * @param [in]         - data lenght
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void SPI_SendData(SPI_Registers *pSPIx, uint8_t *pTxBuffer, uint8_t Len)
{
    while(Len > 0 )
    {
        while (!(pSPIx->SPI_SR & 0x0002)); // Wait until transmit buffer is empty
        pSPIx->SPI_DR = *pTxBuffer;
        while (pSPIx->SPI_SR & 0x0080); // Wait until SPI is not busy
        pTxBuffer++;   
        Len--;
    }
	
}

/********************************************************
  * @fn                 - SPI Peripheral send a bite
  *
  * @brief              - send one bite using SPI
  *
  * @param [in]         - Base address of SPI Peripheral
  * @param [in]         - data bite
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void SPI2_Byte(SPI_Registers *pSPIx, uint8_t data)
{
    while (!(pSPIx->SPI_SR & 0x0002)); // Wait until transmit buffer is empty
    pSPIx->SPI_DR = data;
    while (pSPIx->SPI_SR & 0x0080); // Wait until SPI is not busy
}

