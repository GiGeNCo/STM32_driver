#ifndef INC_SPI_STM32F103C8XX_H_
#define INC_SPI_STM32F103C8XX_H_

#include "stm32f103c8xx.h"

//create configuration structure
//in main code when we'll decide to configure SPI whe have to write our configuration using this structure
typedef struct 
{
    uint8_t SPI_DevMode;
    uint8_t SPI_BusConf;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;            //data fame fragment 8 or 16 bit 
    uint8_t SPI_CPOL;
    uint8_t SPI_CHPA;
    uint8_t SPI_SSM;
    uint8_t SPI_SSI;	
}SPI_Configuration;
//configuration and port structure to configure registers
typedef struct 
{
    SPI_Registers *pSPIx;
    SPI_Configuration SPIConf;	
}SPI_Handler;





//device mode macros, receive or transmit

#define SPI_MODE_MASTER                 1
#define SPI_MODE_SLAVE                  0

// bus config, full duplex, half duplex, simplex tx only, simplex rx only

#define SPI_BUS_FD                      1
#define SPI_BUS_HD                      2
#define SPI_BUS_SIMPLEX_TX              3
#define SPI_BUS_SIMPLEX_RX              4

//clock speed, SPI BR (baud rate) register 

#define SPI_SCLK_SPEED_DIV2             0
#define SPI_SCLK_SPEED_DIV4             1
#define SPI_SCLK_SPEED_DIV8             2
#define SPI_SCLK_SPEED_DIV16            2
#define SPI_SCLK_SPEED_DIV32            4
#define SPI_SCLK_SPEED_DIV64            5
#define SPI_SCLK_SPEED_DIV128           6
#define SPI_SCLK_SPEED_DIV256           7

// dff data frame fragments

#define SPI_DFF_8                       0
#define SPI_DFF_16                      1

//CPOL
#define SPI_CPOL_HIGH                   1
#define SPI_CPOL_LOW                    0

//CPHA
#define SPI_CPHA_HIGH                   1
#define SPI_CPHA_LOW                    0

//SPI ssm Software or hardware slave management
//SSI not affect if SSM is Disabled(LOW,0)
//SSM 1 means we can controll slave using software
//and if I enable SSI with SSM it means that we can controll SS pin using software.

//When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit
#define SPI_SSM_EN                      1       //we can select slave using software
#define SPI_SSM_DI                      0       // we can't select slave using software

//When set (SSI = 1), along with SSM = 1, 
//the master can use an external pin (usually connected to an SS pin of a slave) 
//as an additional software-controlled slave select signal.
#define SPI_SSI_EN                      1
#define SPI_SSI_DI                      0



//Bite defination macros for SPI1 Control register 1
#define SPI_CR1_CHPA                    0
#define SPI_CR1_CPOL                    1
#define SPI_CR1_MSTR                    2
#define SPI_CR1_BR                      3
#define SPI_CR1_SPE                     6
#define SPI_CR1_LSBFIRST                7
#define SPI_CR1_SSI                     8
#define SPI_CR1_SSM                     9
#define SPI_CR1_RXONLY                  10
#define SPI_CR1_DFF                     11
#define SPI_CR1_CRCNEXT                 12
#define SPI_CR1_CRCEN                   13
#define SPI_CR1_BIDIOE                  14
#define SPI_CR1_BIDIMODE                15

//Bite defination macros for SPI Control register 2
#define SPI_CR2_RXDMAEN                 0
#define SPI_CR2_TXDMAEN                 1
#define SPI_CR2_SSOE                    2
#define SPI_CR2_ERRIE                   5
#define SPI_CR2_RXNEIE                  6
#define SPI_CR2_TXNEIE                  7

//Bite defination macros for Status register
#define SPI_SR_RXNE                     0
#define SPI_SR_TXE                      1
#define SPI_SR_CHSIDE                   2
#define SPI_SR_UDR                      3
#define SPI_SR_CRCERR                   4
#define SPI_SR_MODF                     5
#define SPI_SR_OVR                      6
#define SPI_SR_BSY                      7



void RCC_ENABLE_SPI(SPI_Registers *pSPIx);
void SPI_Init(SPI_Handler *pSPI);
void SPI_SendData(SPI_Registers *pSPIx, uint8_t *pTxBuffer, uint8_t Len);
void SPI2_Byte(SPI_Registers *pSPIx, uint8_t data);

#endif