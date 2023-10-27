#ifndef INC_STM32F103C8XX_GPIO_DRIVER_H_
#define INC_STM32F103C8XX_GPIO_DRIVER_H_

#include "stm32f103c8xx.h"



typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinConf;
}GPIO_PinConfig_t;

typedef struct
{
    GPIO_RegDef_t *pGPIOx;   // *pGPIOBaseAddr|| base address of gpio port, which the pon belongs
    GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

//GPIO pin Possible modes

#define     GPIO_MODE_IN                            0 
#define     GPIO_MODE_OUT_10mhz                     1
#define     GPIO_MODE_OUT_2mhz                      2
#define     GPIO_MODE_OUT_50mhz                     3

//GPIO pin configuration



#define     GPIO_INMODE_ANALOG                      0
#define     GPIO_INMODE_FLOATING                    1
#define     GPIO_INMODE_PUPD                        2


#define     GPIO_OUTCONF_PP                         0
#define     GPIO_OUTCONF_OD                         1
#define     GPIO_OUTCONF_ALT_PP                     2
#define     GPIO_OUTCONF_ALT_OD                     3



//also possible modes with interrupt
#define     GPIO_MODE_IT_FT                 4   //falling edge
#define     GPIO_MODE_IT_RT                 5   //rising edge
#define     GPIO_MODE_IT_RFT                6   //rising edge falling edge


//output types
#define     GPIO_OP_TYPE_PP                 0
#define     GPIO_OP_TYPE_OD                 1

//GPIO pin possible output speeds

#define     GPIO_SPEED_IN                    0 
#define     GPIO_SPEED_OUT                   1
#define     GPIO_SPEED_ALTFN                 2
#define     GPIO_SPEED_ANALOG                3

//GPIO pin pull up and pull down configuration macros

#define     GPIO_SPEED_IN                    0 
#define     GPIO_SPEED_OUT                   1
#define     GPIO_SPEED_ALTFN                 2

#define     GPIO_PIN_0                       0
#define     GPIO_PIN_1                       1
#define     GPIO_PIN_2                       2
#define     GPIO_PIN_3                       3
#define     GPIO_PIN_4                       4
#define     GPIO_PIN_5                       5
#define     GPIO_PIN_6                       6
#define     GPIO_PIN_7                       7
#define     GPIO_PIN_8                       8
#define     GPIO_PIN_9                       9
#define     GPIO_PIN_10                      10
#define     GPIO_PIN_11                      11
#define     GPIO_PIN_12                      12
#define     GPIO_PIN_13                      13
#define     GPIO_PIN_14                      14
#define     GPIO_PIN_15                      15

/*####################################################################

                      API Supported by this driver
        for more info about this APIs check function definations

###################################################################*/


//clock set up
void GPIO_PeriClockControll(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);

//init de init 
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//read Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteFromInputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

//IRQ conf and ISR Handling
void GPIO_IRQConf(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t PinNumber);




#endif
