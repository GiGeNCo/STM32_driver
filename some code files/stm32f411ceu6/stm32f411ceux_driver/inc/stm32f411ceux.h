#ifndef INC_STM32F411CEUX_H_
#define INC_STM32F411CEUX_H_

#include "stdint.h"


#define __vo                    volatile


#define AHB1_BASE_ADDR          0x40020000
#define APB1_BASE_ADDR          0x40000000
#define APB2_BASE_ADDR          0x40010000

//RCC BASE ADDR
#define RCC_BASE                0x40023800


//GPIOx BASE addresses all connected to AHP1 BUS
#define GPIOA_BASE              0x40020000
#define GPIOB_BASE              0x40020400
#define GPIOC_BASE              0x40020800
#define GPIOD_BASE              0x40020C00
#define GPIOE_BASE              0x40021000
#define GPIOH_BASE              0x40021C00

//SPI ADDRESSES

#define SPI1_BASE               0x40013000      //APB2
#define SPI2_BASE               0x40003800      //APB1
#define SPI3_BASE               0x40003C00      //APB1
#define SPI4_BASE               0x40013400      //APB2

//I2C Addressses

#define I2C1_BASE               (APB1_BASE_ADDR + 0x5400)
#define I2C2_BASE               (APB1_BASE_ADDR + 0x5800)
#define I2C3_BASE               (APB1_BASE_ADDR + 0x5C00)

//create structures for pheripheral registers RCC

typedef struct 
{
    __vo uint32_t RCC_CR;                       //0x00
    __vo uint32_t RCC_PLLCFGR;                  //0x04
    __vo uint32_t RCC_CFGR;                     //0x08
    __vo uint32_t RCC_CIR;                      //0x0C
    __vo uint32_t RCC_AHB1RSTR;                 //0x10
    __vo uint32_t RCC_AHB2RSTR;                 //0x14
    __vo uint32_t REVERSED1[2];                 //reversed 0x18 - 0x1C
    __vo uint32_t RCC_APB1RSTR;                 //0x20;
    __vo uint32_t RCC_APB2RSTR;                 //0x24
    __vo uint32_t REVERSED2[2];                 //reversed 0x28 - 0x2C
    __vo uint32_t RCC_AHB1ENR;                  //0x30
    __vo uint32_t RCC_AHB2ENR;                  //0x34
    __vo uint32_t REVERSED3[2];                 //reversed 0x38 - 0x3C
    __vo uint32_t RCC_APB1ENR;                  //0x40
    __vo uint32_t RCC_APB2ENR;                  //0x44
    __vo uint32_t REVERSED4[2];                 //reversed 0x48 - 0x4C
    __vo uint32_t RCC_AHB1LPENR;                //0x50
    __vo uint32_t RCC_AHB2LPENR;                //0x54
    __vo uint32_t REVERSED5[2];                 //reversed 0x58 - 0x5C
    __vo uint32_t RCC_APB1LPENR;                //0x60
    __vo uint32_t RCC_APB2LPENR;                //0x64
    __vo uint32_t REVERSED6[2];                 //reversed 0x68 - 0x6C
    __vo uint32_t RCC_BDCR;                     //0x70
    __vo uint32_t RCC_CSR;                      //0x74
    __vo uint32_t REVERSED7[2];                 //reversed 0x78 - 0x7C
    __vo uint32_t RCC_SSCGR;                    //0x80
    __vo uint32_t RCC_PLLI2SCFGR;               //0x84
    __vo uint32_t REVERSED8[2];                 //reversed 0x88 - 0x8C
    
}RCC_Reg;

//GPIO Register structure
typedef struct 
{
    __vo uint32_t GPIO_MODER;                   //0x00
    __vo uint32_t GPIO_OTYPER;                  //0x04
    __vo uint32_t GPIO_OSPEEDR;                 //0x08
    __vo uint32_t GPIO_PUPDR;                   //0x0C
    __vo uint32_t GPIO_IDR;                     //0x10
    __vo uint32_t GPIO_ODR;                     //0x14
    __vo uint32_t GPIO_BSSR;                    //0x18
    __vo uint32_t GPIO_LCKR;                    //0x1C
    __vo uint32_t GPIO_AFRL;                    //0x20
    __vo uint32_t GPIO_AFRH;                    //0x24
    
}GPIO_Reg;

//SPI Register structure

typedef struct
{
    __vo uint32_t SPI_CR1;                      //0x00
    __vo uint32_t SPI_CR2;                      //0x04
    __vo uint32_t SPI_SR;                       //0x08
    __vo uint32_t SPI_DR;                       //0x0C
    __vo uint32_t SPI_CRCPR;                    //0x10
    __vo uint32_t SPI_RXCRCR;                   //0x14
    __vo uint32_t SPI_TXCRCR;                   //0x18
    __vo uint32_t SPI_I2SCFGR;                  //0x1C
    __vo uint32_t SPI_I2SPR;                    //0x20

}SPI_Reg;


//I2C Structure

typedef struct
{
    __vo uint32_t I2C_CR1;                      //0x00 ...
    __vo uint32_t I2C_CR2;
    __vo uint32_t I2C_OAR1;
    __vo uint32_t I2C_OAR2;
    __vo uint32_t I2C_DR;
    __vo uint32_t I2C_SR1;
    __vo uint32_t I2C_SR2;
    __vo uint32_t I2C_CRR;
    __vo uint32_t I2C_TRISE;
    __vo uint32_t I2C_FLTR;

}I2C_Reg_t;


//macros for pheripheral where struct placed
#define GPIOA	((GPIO_Reg *)GPIOA_BASE)
#define GPIOB	((GPIO_Reg *)GPIOB_BASE)
#define GPIOC	((GPIO_Reg *)GPIOC_BASE)
#define GPIOD	((GPIO_Reg *)GPIOD_BASE)
#define GPIOE	((GPIO_Reg *)GPIOE_BASE)
#define GPIOH	((GPIO_Reg *)GPIOH_BASE)

#define SPI1    ((SPI_Reg *)SPI1_BASE)
#define SPI2    ((SPI_Reg *)SPI2_BASE)
#define SPI3    ((SPI_Reg *)SPI3_BASE)
#define SPI4    ((SPI_Reg *)SPI4_BASE)

#define RCC     ((RCC_Reg *)RCC_BASE)

// I2C Peripheral macros, deffinations

#define I2C1    ((I2C_Reg_t *)I2C1_BASE)
#define I2C2    ((I2C_Reg_t *)I2C2_BASE)
#define I2C3    ((I2C_Reg_t *)I2C3_BASE)

// Clock Enable macros for I2Cx

#define I2C1_PCLK_EN()  (RCC->RCC_APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()  (RCC->RCC_APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()  (RCC->RCC_APB1ENR |= (1 << 23))


/************************************************************
*Bit Possition deffinations of I2C peripheral
*************************************************************/
// bit possition defination for I2C_CR1

#define I2C_CR1_PE                      0
#define I2C_CR1_NOSTRETCH               7
#define I2C_CR1_START                   8
#define I2C_CR1_STOP                    9
#define I2C_CR1_ACK                     10
#define I2C_CR1_SWRST                   15

// bit possition defination for I2C_CR2

#define I2C_CR1_FREQ                            0
#define I2C_CR1_ITERREN                         8
#define I2C_CR1_ITEVTEN                         9
#define I2C_CR1_ITBUFEN                         10
#define I2C_CR1_DMAEN                           11
#define I2C_CR1_LAST                            12

// bit possition defination for I2C_OAR1

#define I2C_CR1_ADD0                            0
#define I2C_CR1_ADD7_1                          1
#define I2C_CR1_ADD9_8                          8
#define I2C_CR1_ADDMODE                         15

// bit possition defination for I2C_SR1

#define I2C_CR1_SB                              0
#define I2C_CR1_ADDR                            1
#define I2C_CR1_BTF                             2
#define I2C_CR1_ADD10                           3
#define I2C_CR1_STOPF                           4
#define I2C_CR1_RxNE                            6
#define I2C_CR1_TxE                             7
#define I2C_CR1_BERR                            8
#define I2C_CR1_ARLO                            9
#define I2C_CR1_AF                              10
#define I2C_CR1_OVR                             11
#define I2C_CR1_TIMEOUT                         14

// bit possition defination for I2C_SR2

#define I2C_CR1_MSL                             0
#define I2C_CR1_BUSY                            1
#define I2C_CR1_TRA                             2
#define I2C_CR1_GENCALL                         4
#define I2C_CR1_DUALF                           7

// bit possition defination for I2C_CCR

#define I2C_CR1_CCR11_0                         0
#define I2C_CR1_DUTY                            14
#define I2C_CR1_F_S                             15




//usable macros
#define HIGH            1
#define LOW             0
#define ENABLE          1
#define DISABLE         0

#include "gpio_stm32f411ceux.h"
#include "i2c_stm32f411ceux.h"
//#include "SPI_STM32F411CEUx.h"


#endif