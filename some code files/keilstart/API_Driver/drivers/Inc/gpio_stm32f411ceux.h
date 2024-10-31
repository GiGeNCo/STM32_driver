#ifndef INC_GPIO_STM32F411CEUX_H_
#define INC_GPIO_STM32F411CEUX_H_

#include "stm32f411ceux.h"

//this is a configuration structure for a gpio pin

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;			/*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

//this is a hande structure for a gpio pin

typedef struct 
{
	GPIO_RegDef_t *pGPIOx;				//this holds base address of our selected gpio port
	GPIO_PinConfig_t *GPIO_PinConfig;	//there we have to write pin settings
}GPIO_Handle_t;

//GPIO Pin Numbers:
#define GPIO_PIN_NO_0				0
#define GPIO_PIN_NO_1				1
#define GPIO_PIN_NO_2				2
#define GPIO_PIN_NO_3				3
#define GPIO_PIN_NO_4				4
#define GPIO_PIN_NO_5				5
#define GPIO_PIN_NO_6				6
#define GPIO_PIN_NO_7				7
#define GPIO_PIN_NO_8				8
#define GPIO_PIN_NO_9				9
#define GPIO_PIN_NO_10				10
#define GPIO_PIN_NO_11				11
#define GPIO_PIN_NO_12				12
#define GPIO_PIN_NO_13				13
#define GPIO_PIN_NO_14				14
#define GPIO_PIN_NO_15				15

/*
* GPIO pin Possible Modes
* @GPIO_PIN_MODES
*/
#define GPIO_MODE_INPUT				0
#define GPIO_MODE_OUTPUT			1
#define GPIO_MODE_ATLF				2
#define GPIO_MODE_ANALOG			3

#define GPIO_MODE_IT_FT				4	//ft falling edge (t as triger)
#define GPIO_MODE_IT_RT				5	//rising edge
#define GPIO_MODE_IT_RFT			6	//rising as weel as falling edge

//GPIO Output possible types
#define GPIO_OP_TYPE_PP				0	//push pull type
#define GPIO_OP_TYPE_OD				1	//Open Drain

//GPIO Output possible speeds
#define GPIO_SPEED_LOW				0
#define GPIO_SPEED_MEDIUM			1
#define GPIO_SPEED_FAST				2
#define GPIO_SPEED_HIGH				3

//GPIO PULL Up and Pull Down configuration macros
#define GPIO_NO_PUPD				0
#define GPIO_PIN_PU					1
#define GPIO_PIN_PD					2




//peripheral clokc setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);


//init de-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t VALUE);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

//IRQ COnfig and ISR Handling

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t PinNumber);









#endif