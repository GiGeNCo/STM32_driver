#ifndef INC_STM32F103C8_SPI_H_
#define INC_STM32F103C8_SPI_H_

#include <stdint.h>
#include "stm32f103c8xx.h"

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

}SPI_Conf_t;

typedef struct
{
    SPI_RegDef_t *pSPIx;
    SPI_Conf_t SPIConf;
}SPI_Handle_t;

/*******************************************************************
                    GIORGI LALUASHVILI
                        SPI DRIVER
                SPI Configuration functions
*******************************************************************/
/*
 *       Clock enable or disable function
 */

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t  EnOrDi);

/*
 *       init   deinit
 */

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*
 *       Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);


/*
 *       SPI conf and ISR Handling
 */

//IRQ conf and ISR Handling
void SPI_IRQInterruptConf(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);





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
#define SPI_SSM_SW                      0
#define SPI_SSM_HW                      1

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN     1
#define SPI_SSM_DI     0

#define SPI_TXE_FLAG                    (1<<SPI_SR_TXE)
#define SPI_RXNE_FLAG                   (1<<SPI_SR_TXE)
#define SPI_BUSY_FLAG                   (1<<SPI_SR_TXE)


#endif