#ifndef INC_I2C_STM32F411CEUX_H_
#define INC_I2C_STM32F411CEUX_H_

#include "stm32f411ceux.h"



typedef struct
{
    uint32_t    I2C_SCLSpeed;
    uint8_t     I2C_DeviceAddr;
    uint8_t     I2C_ACKControl;
    uint16_t    I2C_FMDutyCycle;
}I2C_Config_t;

typedef struct
{
    I2C_Reg_t     *pI2Cx;
    I2C_Config_t  I2C_Config;
}I2C_Handle_t;


/*
 * I2C_SCLSpeed;
 */

//standard mode
#define I2C_SCL_SPEED_SM                100000
//fast mode
#define I2C_SCL_SPEED_FM2K              200000
//fast mode
#define I2C_SCL_SPEED_FM4K              400000


/*
 * I2C_ACK Control;
 */

#define I2C_ACK_ENABLE                  1
#define I2C_ACK_DISABLE                 0

/*
 * I2C_FM Duty Cycle;
 */

#define I2C_FM_DUTY_2                   0
#define I2C_FM_DUTY_16_9                1


/**************************************************************************
 *                      APIs supported by this driver
 *      For more information about the APIs check the function deffinations
 *
 *************************************************************************/

// Peripheral Clock Setup
void I2C_PeriClockControl (I2C_Reg_t *pI2Cx, uint8_t EnOrDi);

// Init && De-Init
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_Reg_t *pI2Cx);

// Data Send && Receive
void I2C_SendData(I2C_Reg_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len);
void I2C_ReceiveData(I2C_Reg_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len);

uint8_t I2C_SendDataIT(I2C_Reg_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len);
uint8_t I2C_ReceiveDataIT(I2C_Reg_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len);

//IRQ COnfiguration and ISR handling
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void I2C_PriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

//Other peripheral Control APIs
void I2C_PeripheralControl(I2C_Reg_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_Reg_t *pI2Cx, uint32_t FlagName);

//application callback
void I2C_ApplicationEventCallBack(I2C_Handle_t *pI2CHandle, uint8_t AppEV);






#endif

