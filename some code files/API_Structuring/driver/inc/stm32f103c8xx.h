#ifndef INC_STM32F103C8XX_H_
#define INC_STM32F103C8XX_H_
#include <stdint.h>


#define __vo                    volatile

#define FLASH_BASEADDR          0x08000000U     //64kb 
#define SRAM_BASEADDR           0x20000000U     //20kb	// 20*1024 = 20 480 byte || 20480 in hex is 0x5000
#define ROM_BASEADDR            0x1FFFF000U     //system memory in flash datasheet
#define RCC_BASEADDR            0x40021000


#define APB2PERIPH_BASEADDR		0x40010000
#define APB1PERIPH_BASEADDR		0x40000000


//peripherials which are hanging on apb2
#define GPIOA_BASEADDR          (APB2PERIPH_BASEADDR+0x0800)
#define GPIOB_BASEADDR          (APB2PERIPH_BASEADDR+0x0C00)
#define GPIOC_BASEADDR          (APB2PERIPH_BASEADDR+0x1000)
#define GPIOD_BASEADDR          (APB2PERIPH_BASEADDR+0x1400)
#define GPIOE_BASEADDR          (APB2PERIPH_BASEADDR+0x1800)
#define GPIOF_BASEADDR          (APB2PERIPH_BASEADDR+0x1C00)
#define GPIOG_BASEADDR          (APB2PERIPH_BASEADDR+0x2000)



//peripherials which are hanging on apb2
#define GPIOA_BASEADDR          (APB2PERIPH_BASEADDR+0x0800)
#define GPIOB_BASEADDR          (APB2PERIPH_BASEADDR+0x0C00)
#define GPIOC_BASEADDR          (APB2PERIPH_BASEADDR+0x1000)
#define GPIOD_BASEADDR          (APB2PERIPH_BASEADDR+0x1400)
#define GPIOE_BASEADDR          (APB2PERIPH_BASEADDR+0x1800)
#define GPIOF_BASEADDR          (APB2PERIPH_BASEADDR+0x1C00)
#define GPIOG_BASEADDR          (APB2PERIPH_BASEADDR+0x2000)


#define SPI1_BASE               (APB2PERIPH_BASEADDR+0x3000)

#define USART1                  (APB2PERIPH_BASEADDR+0x3800)

#define EXTI_BASEADDR           (APB2PERIPH_BASEADDR+0x0400)

#define AIFO_BASEADDR           (APB2PERIPH_BASEADDR+0x0000)

//Peripherials which are hanging on APB1
#define I2C1_BASE               (APB1PERIPH_BASEADDR+0x5400)
#define I2C2_BASE               (APB1PERIPH_BASEADDR+0x5800)

#define SPI2_BASE               (APB1PERIPH_BASEADDR+0x3800)
#define SPI3_BASE               (APB1PERIPH_BASEADDR+0x3C00)

#define USART2                  (APB1PERIPH_BASEADDR+0x4400)
#define USART3                  (APB1PERIPH_BASEADDR+0x4800)

#define UART4                   (APB1PERIPH_BASEADDR+0x4C00)
#define UART5                   (APB1PERIPH_BASEADDR+0x5000)


//Register Structures

//GPIO Registers
typedef struct 
{
	__vo uint32_t CR[2];                //Port configuration register low(0)0x00  and high(1) 0x04
	//__vo uint32_t CRL;                //Port configuration register high     0x00
	//__vo uint32_t CRH;                //Port configuration register high     0x04
	__vo uint32_t IDR;                //input data register                  0x08
	__vo uint32_t ODR;                //output data register                 0x0c
	__vo uint32_t BSRR;               //bit set/reset register               0x10
	__vo uint32_t BRR;                //bit reset register                   0x14
	__vo uint32_t LCKR;               //Port configuration lock register     0x18
	
} GPIO_Registers;


//RCC Registers
typedef struct 
{
	__vo uint32_t CR;                //Clock control register            0x00
	__vo uint32_t CFGR;              //Clock configuration register      0x04
	__vo uint32_t CIR;               //Clock interrupt register          0x08
	__vo uint32_t APB2RSTR;          //APB2 peripheral reset register    0x0C
	__vo uint32_t APB1RSTR;          //APB1 peripheral reset register    0x10
	__vo uint32_t AHBENR;            //AHB Peripheral Clock enable register 0x14
	__vo uint32_t APB2ENR;           //APB2 peripheral clock enable register 0x18
	__vo uint32_t APB1ENR;           //APB1 peripheral clock enable register 0x1C
	__vo uint32_t BDCR;              //Backup domain control register    0x20
	__vo uint32_t CSR;               //Control/status register           0x24
	__vo uint32_t AHBSTR;            //AHB peripheral clock reset register 0x28
	__vo uint32_t CFGR2;             //Clock configuration register2     0x2C	
}RCC_Registers;


//EXTI_Registers
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_Registers;


//Alternate function IO registers
typedef struct
{
  __vo uint32_t EVCR;
  __vo uint32_t MAPR;
  __vo uint32_t EXTR[4];
  __vo uint32_t MAPR2;
  
}AFIO_Registers;

typedef struct
{

    __vo uint32_t SPI_CR1;
    __vo uint32_t SPI_CR2;
    __vo uint32_t SPI_SR;
    __vo uint32_t SPI_DR;
    __vo uint32_t SPI_CRCPR;
    __vo uint32_t SPI_RXCRCR;
    __vo uint32_t SPI_TXCRCR;
    __vo uint32_t SPI_I2SCFGR;
    __vo uint32_t SPI_I2SPR;

}SPI_Registers;


//Create macros to access address of pheriperal with their structure pointer
//every pharipheral has their own address so we have structures with their registers
//I have to create pointers of this structure what are located on pheriperal addresses
//ვქმნით მაკროს პერიფერიალის მისამართზე, რეგისტრების სტრუქტურის პოინტერის. როდესაც გამოვიძახებთ ამ მაკროს
//პერიფერიალის მისამართზე გვაქვს სტრუქტურა რომლის ელემენტებიც იკავებენ შესაბამისი რეგისტრების მისამართებს
//აღნიშნული მაკროს ელემენტებზე კონფიგურაციის გაწერით შეიცვლება შესაბამისი რეგისტრის კონფიგურაცია.

#define GPIOA	((GPIO_Registers *)GPIOA_BASEADDR)
#define GPIOB	((GPIO_Registers *)GPIOB_BASEADDR)
#define GPIOC	((GPIO_Registers *)GPIOC_BASEADDR)
#define GPIOD	((GPIO_Registers *)GPIOD_BASEADDR)
#define GPIOE	((GPIO_Registers *)GPIOE_BASEADDR)
#define GPIOF	((GPIO_Registers *)GPIOF_BASEADDR)
#define GPIOG	((GPIO_Registers *)GPIOG_BASEADDR)


#define RCC     ((RCC_Registers *)RCC_BASEADDR)
#define EXTI	((EXTI_Registers *)EXTI_BASEADDR)
#define AIFO	((AFIO_Registers *)AIFO_BASEADDR)


#define RCC_EN_PA       (RCC->APB2ENR |= (1 << 2))
#define RCC_EN_PB       (RCC->APB2ENR |= (1 << 3))
#define RCC_EN_PC       (RCC->APB2ENR |= (1 << 4))
#define RCC_EN_PD       (RCC->APB2ENR |= (1 << 5))
#define RCC_EN_PE       (RCC->APB2ENR |= (1 << 6))
#define RCC_EN_PF       (RCC->APB2ENR |= (1 << 7))
#define RCC_EN_PG       (RCC->APB2ENR |= (1 << 8))


#define SPI1                   ((SPI_Registers*)SPI1_BASE)
#define SPI2                   ((SPI_Registers*)SPI2_BASE)
#define SPI3                   ((SPI_Registers*)SPI3_BASE)


//usable macros
#define HIGH            1
#define LOW             0
#define Enable          1
#define Disable         0


#include "GPIO_STM32F103C8xx.h"
#include "SPI_STM32F103C8xx.h"

#endif
