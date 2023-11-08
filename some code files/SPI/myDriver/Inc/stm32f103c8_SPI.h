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
void SPI_DeInit(SPI_Handle_t *pSPIx);


/*
 *       Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


/*
 *       SPI conf and ISR Handling
 */

//IRQ conf and ISR Handling
void SPI_IRQInterruptConf(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);



#endif