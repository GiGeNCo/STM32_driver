#include "gpio_stm32f411ceux.h"



/********************************************************
  * @fn                 - GPIO_Init
  *
  * @brief              - this func initialize user gpio config
  *
  * @param [in]         - *pGPIOx structure(GPIO_RegDef_t) where is  GPIO Registers
  * @param [in]         - EnOrDi Enable or disable clock
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
		else if(pGPIOx == GPIOJ)
		{
			GPIOJ_PCLK_EN();
		}
		else if(pGPIOx == GPIOK)
		{
			GPIOK_PCLK_EN();
		}
	}


}

/********************************************************
  * @fn                 - GPIO_Init
  *
  * @brief              - this func initialize user gpio config
  *
  * @param [in]         - *pGPIOHandle structure where is 2 more structure inside 1 *pGPIOx GPIO Registers
						- and *GPIO_PinConfig where would be user settings (configuration) about pin
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	//1. configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig->GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig->GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(3 << pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber); // clear
		pGPIOHandle->pGPIOx->MODER |= temp;
		temp = 0;
	}
	
	//2. configure speed
	temp = (pGPIOHandle->GPIO_PinConfig->GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(3 << pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber); // clear
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;
	//3. configure pull up pull down
	temp = (pGPIOHandle->GPIO_PinConfig->GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(3 << pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber); // clear
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;
	//4. configure output type
	temp = (pGPIOHandle->GPIO_PinConfig->GPIO_PinOPType <<  pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber); // clear
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;
	//5. configure the alternate function
	if (pGPIOHandle->GPIO_PinConfig->GPIO_PinAltFunMode == GPIO_MODE_ATLF)
	{
		uint32_t temp1 = 0, temp2 = 0;
		temp1 = pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig->GPIO_PinNumber % 8;
		
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));		//clear
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig->GPIO_PinAltFunMode << (4 * temp2));
		
	}	
}
/********************************************************
  * @fn                 - GPIO_DeInit
  *
  * @brief              - this func reset  gpio config
  *
  * @param [in]         - 
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
		{
			GPIOA_REG_RESET();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_REG_RESET();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_REG_RESET();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_REG_RESET();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_REG_RESET();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_REG_RESET();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_REG_RESET();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_REG_RESET();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_REG_RESET();
		}
		else if(pGPIOx == GPIOJ)
		{
			GPIOJ_REG_RESET();
		}
		else if(pGPIOx == GPIOK)
		{
			GPIOK_REG_RESET();
		}


}

/********************************************************
  * @fn                 - GPIOI_nit
  *
  * @brief              - this func read from input pin
  *
  * @param [in]         - *pGPIOx structure(GPIO_RegDef_t) where is  GPIO Registers
  * @param [in]         - PinNumber user selected pin
  * @param [in]         - 
  *
  * @return             - return uint8_t data from Pin 1 or 0
  *
  * @note               - none
********************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}


/********************************************************
  * @fn                 - GPIOI_nit
  *
  * @brief              - this func read from input port
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - PinNumber user selected pin
  * @param [in]         - 
  *
  * @return             - return uint16_t data from Port
  *
  * @note               - none
********************************************************/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;

}

/********************************************************
  * @fn                 - GPIO_writeTo output pin
  *
  * @brief              - this func initialize write to pin
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - PinNumber user selected pin
  * @param [in]         - Value user value
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		//write 1 to output data register at the bit field correspondig to the pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}
/********************************************************
  * @fn                 - GPIO_writeTo output port
  *
  * @brief              - this func write to port
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - Value user value
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t VALUE)
{
	pGPIOx->ODR = VALUE;
}
/********************************************************
  * @fn                 - GPIO_toggle pin
  *
  * @brief              - this func toggle pin
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - PinNumber user selected pint to toggle
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}


/********************************************************
  * @fn                 - GPIO_IRQ Config
  *
  * @brief              - this func configure IRQ
  *
  * @param [in]         - IRQNumber select IRQ number
  * @param [in]         - select IRQPriority
  * @param [in]         - EnOrDi enable or disable IRQ
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi)
{


}

/********************************************************
  * @fn                 - GPIO_IRQ Handling
  *
  * @brief              - this func HANDLE IRQ
  *
  * @param [in]         - PinNumber where to happen interrupt
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{


}
