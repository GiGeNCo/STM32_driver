#ifndef INC_STM32F103C8XX_H_
#define INC_STM32F103C8XX_H_

#include <stdint.h>


#define __vo                    volatile

//base address of flash and sram memories

#define FLASH_BASEADDR          0x08000000U     //64kb 
#define SRAM_BASEADDR           0x20000000U     //20kb  20*1024 = 20 480 byte || 20480 in hex is 0x5000
#define ROM_BASEADDR            0x1FFFF000U     //system memory in flash datasheet


#define PERIPH_BASEADDR         0x40000000U
#define APB1PERIPH_BASEADDR     PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR     0x40010000U
#define AHBPERIPH_BASEADDR      0x40018000U

#define RCC_BASEADDR            0x40021000UL

#define EXTI_BASEADDR           (APB2PERIPH_BASEADDR+0x0400)

//#define AHB2PERIPH_BASE     

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

//Peripherials which are hanging on APB1
#define I2C1_BASE               (APB1PERIPH_BASEADDR+0x5400)
#define I2C2_BASE               (APB1PERIPH_BASEADDR+0x5800)

#define SPI2_BASE               (APB1PERIPH_BASEADDR+0x3800)
#define SPI3_BASE               (APB1PERIPH_BASEADDR+0x3C00)

#define USART2                  (APB1PERIPH_BASEADDR+0x4400)
#define USART3                  (APB1PERIPH_BASEADDR+0x4800)

#define UART4                   (APB1PERIPH_BASEADDR+0x4C00)
#define UART5                   (APB1PERIPH_BASEADDR+0x5000)





//register stucture

typedef struct
{
  __vo uint32_t CR[2];                //Port configuration register low(0)0x00  and high(1) 0x04
  //__vo uint32_t CRH;                //Port configuration register high     0x04
  __vo uint32_t IDR;                //input data register                  0x08
  __vo uint32_t ODR;                //output data register                 0x0c
  __vo uint32_t BSRR;               //bit set/reset register               0x10
  __vo uint32_t BRR;                //bit reset register                   0x14
  __vo uint32_t LCKR;               //Port configuration lock register     0x18
}GPIO_RegDef_t;


typedef struct
{
  __vo uint32_t _CR;                //Clock control register            0x00
  __vo uint32_t _CFGR;              //Clock configuration register      0x04
  __vo uint32_t _CIR;               //Clock interrupt register          0x08
  __vo uint32_t _APB2RSTR;          //APB2 peripheral reset register    0x0C
  __vo uint32_t _APB1RSTR;          //APB1 peripheral reset register    0x10
  __vo uint32_t _AHBENR;            //AHB Peripheral Clock enable register 0x14
  __vo uint32_t _APB2ENR;           //APB2 peripheral clock enable register 0x18
  __vo uint32_t _APB1ENR;           //APB1 peripheral clock enable register 0x1C
  __vo uint32_t _BDCR;              //Backup domain control register    0x20
  __vo uint32_t _CSR;               //Control/status register           0x24
  __vo uint32_t _AHBSTR;            //AHB peripheral clock reset register 0x28
  __vo uint32_t _CFGR2;             //Clock configuration register2     0x2C


}RCC_RegDef_t;


/*
 *  exti pheripherial register defination structure
 */

typedef struct
{
    __vo uint32_t IMR;                   //...definations ...
    __vo uint32_t EMR;
    __vo uint32_t RTSR;
    __vo uint32_t FTSR;
    __vo uint32_t PR;

}EXTI_RegDef_t;


#define GPIOA                   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                   ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                   ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                   ((GPIO_RegDef_t*)GPIOG_BASEADDR)

#define RCC                     ((EXTI_RegDef_t*)RCC_BASEADDR)


#define EXTI                    ((EXTI_RegDef_t *)EXTI_BASE_ADDR)

//clock enable macros for GPIOx periph

//GPIOA_PERI_CLOCK_ENABLE short name PA_PCLK_EN
#define PA_PCLK_EN()            (RCC->_APB2ENR |= (1 << 2))
//same rules for same register from GPIOA to GPIOG
#define PB_PCLK_EN()            (RCC->_APB2ENR |= (1 << 3))
#define PC_PCLK_EN()            (RCC->_APB2ENR |= (1 << 4))
#define PD_PCLK_EN()            (RCC->_APB2ENR |= (1 << 5))
#define PE_PCLK_EN()            (RCC->_APB2ENR |= (1 << 6))
#define PF_PCLK_EN()            (RCC->_APB2ENR |= (1 << 7))
#define PG_PCLK_EN()            (RCC->_APB2ENR |= (1 << 8))

//Clock enable macros for I2C

#define I2C1_PCLK_EN()          (RCC->_APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()          (RCC->_APB1ENR |= (1 << 22))


//clock enable macros for SPI

#define SPI1_PCLK_EN()          (RCC->_APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()          (RCC->_APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()          (RCC->_APB1ENR |= (1 << 15))

//clock enable macros for UART
#define USART1_PCLK_EN()        (RCC->_APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()        (RCC->_APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()        (RCC->_APB1ENR |= (1 << 18))

#define UART4_PCLK_EN()         (RCC->_APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()         (RCC->_APB1ENR |= (1 << 20))




//clock disavble macros for gpio

#define PA_PCLK_DI()    (RCC->_APB2ENR &= ~(1 << 2))




// Some Generic macros

#define ENABLE                        1
#define DISABLE                       0
#define SET                          ENABLE
#define RESET                        DISABLE
#define GPIO_PIN_SET                 ENABLE
#define GPIO_PIN_RESET               DISABLE


#include "stm32f103c8xx.h_gpio_driver.h"


#endif

