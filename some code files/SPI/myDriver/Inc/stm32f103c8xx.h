#ifndef INC_STM32F103C8XX_H_
#define INC_STM32F103C8XX_H_

#include <stdint.h>


#define __vo                    volatile

//define NVIC REGs

#define NVIC_ISER0              (( __vo uint32_t* )0xE000E100)
#define NVIC_ISER1              (( __vo uint32_t* )0xE000E104)
#define NVIC_ISER2              (( __vo uint32_t* )0xE000E108)
#define NVIC_ISER3              (( __vo uint32_t* )0xE000E10C)


#define NVIC_ICER0              (( __vo uint32_t* )0XE000E180)
#define NVIC_ICER1              (( __vo uint32_t* )0XE000E184)
#define NVIC_ICER2              (( __vo uint32_t* )0XE000E188)
#define NVIC_ICER3              (( __vo uint32_t* )0XE000E18C)

//define irq priority registert calculation

#define NVIC_PR_BASE_ADDR       (( __vo uint32_t* )0xE000E400) 

//interrupt priority reserved bits amount
#define NO_PR_BITS_IMPLEMENTED  4



//base address of flash and sram memories

#define FLASH_BASEADDR          0x08000000U     //64kb 
#define SRAM_BASEADDR           0x20000000U     //20kb	// 20*1024 = 20 480 byte || 20480 in hex is 0x5000
#define ROM_BASEADDR            0x1FFFF000U     //system memory in flash datasheet


#define PERIPH_BASEADDR         0x40000000U
#define APB1PERIPH_BASEADDR     PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR     0x40010000U
#define AHBPERIPH_BASEADDR      0x40018000U

#define RCC_BASEADDR            0x40021000UL
//#define AHB2PERIPH_BASE     

//peripherials which are hanging on apb2
#define GPIOA_BASEADDR          (APB2PERIPH_BASEADDR+0x0800)
#define GPIOB_BASEADDR          (APB2PERIPH_BASEADDR+0x0C00)
#define GPIOC_BASEADDR          (APB2PERIPH_BASEADDR+0x1000)
#define GPIOD_BASEADDR          (APB2PERIPH_BASEADDR+0x1400)
#define GPIOE_BASEADDR          (APB2PERIPH_BASEADDR+0x1800)
#define GPIOF_BASEADDR          (APB2PERIPH_BASEADDR+0x1C00)
#define GPIOG_BASEADDR          (APB2PERIPH_BASEADDR+0x2000)



#define EXTI_BASEADDR           (APB2PERIPH_BASEADDR+0x0400)

#define AIFO_BASEADDR           (APB2PERIPH_BASEADDR+0x0000)

//Peripherials which are hanging on APB1
#define I2C1_BASEADDR           (APB1PERIPH_BASEADDR+0x5400)
#define I2C2_BASEARRD           (APB1PERIPH_BASEADDR+0x5800)

#define SPI1_BASEADDR           (APB2PERIPH_BASEADDR+0x3000)
#define SPI2_BASEADDR           (APB1PERIPH_BASEADDR+0x3800)
#define SPI3_BASEADDR           (APB1PERIPH_BASEADDR+0x3C00)

#define USART1_BASEADDR         (APB2PERIPH_BASEADDR+0x3800)
#define USART2_BASEADDR         (APB1PERIPH_BASEADDR+0x4400)
#define USART3_BASEADDR         (APB1PERIPH_BASEADDR+0x4800)
#define UART4_BASEADDR          (APB1PERIPH_BASEADDR+0x4C00)
#define UART5_BASEADDR          (APB1PERIPH_BASEADDR+0x5000)




//register stucture

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
}GPIO_RegDef_t;


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


}RCC_RegDef_t;

typedef struct
{
  __vo uint32_t IMR;
  __vo uint32_t EMR;
  __vo uint32_t RTSR;
  __vo uint32_t FTSR;
  __vo uint32_t SWIER;
  __vo uint32_t PR;


}EXTI_RegDef_t;

typedef struct
{
  __vo uint32_t EVCR;
  __vo uint32_t MAPR;
  __vo uint32_t EXTR[4];
  __vo uint32_t MAPR2;
  
}AFIO_RegDef_t;


typedef struct
{
    __vo uint32_t CRx[2];
    __vo uint32_t SR;
    __vo uint32_t DR;
    __vo uint32_t CRCPR;
    __vo uint32_t RXCRCR;
    __vo uint32_t TXCRCR;
    __vo uint32_t I2SCFGR;
    __vo uint32_t I2SPR;

}SPI_RegDef_t;



#define GPIOA                   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                   ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                   ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                   ((GPIO_RegDef_t*)GPIOG_BASEADDR)

#define RCC                     ((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI                    ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define AIFO                    ((AFIO_RegDef_t*)AIFO_BASEADDR)


#define SPI1                   ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2                   ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3                   ((SPI_RegDef_t*)SPI3_BASEADDR)


//clock enable macros for GPIOx periph

//GPIOA_PERI_CLOCK_ENABLE short name PA_PCLK_EN
#define PA_PCLK_EN()            (RCC->APB2ENR |= (1 << 2))
//same rules for same register from GPIOA to GPIOG
#define PB_PCLK_EN()            (RCC->APB2ENR |= (1 << 3))
#define PC_PCLK_EN()            (RCC->APB2ENR |= (1 << 4))
#define PD_PCLK_EN()            (RCC->APB2ENR |= (1 << 5))
#define PE_PCLK_EN()            (RCC->APB2ENR |= (1 << 6))
#define PF_PCLK_EN()            (RCC->APB2ENR |= (1 << 7))
#define PG_PCLK_EN()            (RCC->APB2ENR |= (1 << 8))

//Clock enable macros for I2C

#define I2C1_PCLK_EN()          (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()          (RCC->APB1ENR |= (1 << 22))


//clock enable macros for SPI

#define SPI1_PCLK_EN()          (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()          (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()          (RCC->APB1ENR |= (1 << 15))

//clock enable macros for UART
#define USART1_PCLK_EN()        (RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()        (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()        (RCC->APB1ENR |= (1 << 18))

#define UART4_PCLK_EN()         (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()         (RCC->APB1ENR |= (1 << 20))

//clock  enable macro for AIFO

#define AIFO_PCLK_EN()          (RCC->APB2ENR |= (1 << 0))



//clock disable macros for gpio

#define PA_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 2))

//reset gpiox pheriperal
#define PA_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 2));	(RCC->APB2RSTR &= ~(1 << 2)); } while(0)
#define PB_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 3));	(RCC->APB2RSTR &= ~(1 << 3)); } while(0)
#define PC_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 4));	(RCC->APB2RSTR &= ~(1 << 4)); } while(0)
#define PD_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 5));	(RCC->APB2RSTR &= ~(1 << 5)); } while(0)
#define PE_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 6));	(RCC->APB2RSTR &= ~(1 << 6)); } while(0)
#define PF_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 7));	(RCC->APB2RSTR &= ~(1 << 7)); } while(0)
#define PG_REG_RESET()			do{ (RCC->APB2RSTR |= (1 << 8));	(RCC->APB2RSTR &= ~(1 << 8)); } while(0)


#define GPIO_BASEADDR_TO_CODE(x)    (   (x == GPIOA)?0:\
                                        (x == GPIOB)?1:\
                                        (x == GPIOB)?2:\
                                        (x == GPIOB)?3:\
                                        (x == GPIOB)?4:\
                                        (x == GPIOB)?5:\
                                        (x == GPIOB)?6:\
                                        (x == GPIOB)?7:0    )






#define IRQ_NO_EXTI0                6
#define IRQ_NO_EXTI1                7
#define IRQ_NO_EXTI2                8
#define IRQ_NO_EXTI3                9
#define IRQ_NO_EXTI4                10
#define IRQ_NO_EXTI9_5              23
#define IRQ_NO_EXTI15_10            40


// Some Generic macros

#define ENABLE                        1
#define DISABLE                       0
#define SET                          ENABLE
#define RESET                        DISABLE
#define GPIO_PIN_SET                 ENABLE
#define GPIO_PIN_RESET               DISABLE


#include "stm32f103c8xx.h_gpio_driver.h"
#include "stm32f103c8_SPI.h"


#endif

