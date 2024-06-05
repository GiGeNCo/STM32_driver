#ifndef INC_GPIO_STM32F103C8XX_H_
#define INC_GPIO_STM32F103C8XX_H_

#include "stm32f103c8xx.h"



//create configuration structure
//in main code when we'll decide to configure GPIO whe have to write our configuration using this structure
typedef struct 
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_Mode;
	uint8_t GPIO_Cfn;
	uint8_t	GPIO_Interrupt;	
}GPIO_Configuration;
//configuration and port structure to configure registers
typedef struct 
{
	GPIO_Registers	*pGPIOx;
	GPIO_Configuration GPIO_Configuration;	
}GPIO_Handler;


//create macros for GPIO modes
#define INPUT                           0
#define OUTPUT_10MHZ                    1
#define OUTPUT_2MHZ                     2
#define OUTPUT_50MHZ                    3

//macros for GPIO OUTPUT configuration
#define GPIO_OUT_PUSH_PULL					0
#define GPIO_OUT_OPEN_DRAIN					1
#define GPIO_ALT_OUT_PUSH_PULL				2
#define GPIO_ALT_OUT_OPEN_DRAIN				3


//macros for GPIO OUTPUT configuration
#define GPIO_IN_ANALOG						0
#define GPIO_IN_FLOATING					1
#define GPIO_IN_PULL_UP_PULL_DOWN			2

//also possible modes with interrupt
#define GPIO_MODE_IT_FT                 4   //falling edge
#define GPIO_MODE_IT_RT                 5   //rising edge
#define GPIO_MODE_IT_RFT                6   //rising edge falling edge


void Enable_RCC(GPIO_Registers *pGPIO);
void GPIO_Init(GPIO_Handler *pGPIO);
void GPIO_Write(GPIO_Registers *pGPIO, uint8_t pinNumber,uint8_t value );
uint8_t GPIO_Read(GPIO_Registers *pGPIO, uint8_t pinNumber);


#endif