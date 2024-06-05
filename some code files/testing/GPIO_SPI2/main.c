#include <stdint.h>
#include "string.h"

/*
*       SPI2
*       PB12 --> NSS
*       PB13 --> SCK
*       PB14 --> MISO
*       PB15 --> MOSI
*       ALF Function    PB13
*/

// Define base addresses for peripherals
#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000
#define GPIOB_BASE      0x40010C00
#define SPI2_BASE       0x40003800


// Define register addresses for RCC, GPIOA, EXTI, and AFIO
#define RCC_APB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x1C))
#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOC_CRH       (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))
#define GPIOC_BSRR      (*(volatile uint32_t*)(GPIOC_BASE + 0x10))

#define GPIOB_CRH       (*(volatile unsigned int *)(GPIOB_BASE + 0x04))
#define GPIOB_ODR       (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOB_BSRR      (*(volatile uint32_t*)(GPIOB_BASE + 0x10))


// Bit masks
#define RCC_APB2ENR_IOPCEN      (1 << 4)
#define RCC_APB2ENR_IOPBEN      (1 << 3)
#define RCC_APB1ENR_SPI2        (1 << 14)



#define GPIO_CRH_CNF2           (0 << 22)
#define GPIO_CRH_MODE2          (1 << 20)


#define SPI2_CR1            (*(volatile uint32_t*)(SPI2_BASE + 0x00))
#define SPI2_CR2            (*(volatile uint32_t*)(SPI2_BASE + 0x04))
#define SPI2_DR             (*(volatile uint32_t*)(SPI2_BASE + 0x0C))
#define SPI2_SR             (*(volatile uint32_t*)(SPI2_BASE + 0x08))





void GPIO_Config()
{
    /*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
    1 - Enable GPIO Clock
    2 - Set the Required pin in the INPUT mode
    3 - Configure the pull-up/pull-down According your requirement
    ********************************************************/
    
    // Enable clock for GPIOC
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
    
    // Configure PC13 as input with pull-down (input mode, CNF2 = 10)
    GPIOC_CRH &= ~((0xF) << 20);       // Clear MODE13 and CNF13 bits
    GPIOC_CRH |= (GPIO_CRH_MODE2);        //Configure mode output 10 mhz
    GPIOC_CRH |= (GPIO_CRH_CNF2);     // Set CNF13 to OUT mode push-pull
    
    
    
    // Configure PA2 as input with pull-down (input mode, CNF2 = 10)
    GPIOC_CRH &= ~((0xF) << 24);       // Clear MODE14 and CNF14 bits
    GPIOC_CRH |= (1 << 24);        //Configure mode output 10 mhz
    GPIOC_CRH |= (0 << 26);     // Set CNF14 to OUT mode push-pull


}
void SPI2_Config()
{
    
    //enable SPI2 on RCCAPB1ENR
    RCC_APB1ENR |= RCC_APB1ENR_SPI2;
    // Enable clock for GPIOA
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    // Configure PB13 (SCK), PB14 (MISO), PB15 (MOSI) as alternate function push-pull PB12 (NSS) as output pushpull
    
    
    //SCK pin configuration output alternate func
    GPIOB_CRH &= ~(0xF << 20);  //Clear MODE13 and CFN13 on GPIO register B
    GPIOB_CRH &= ~(0xF << 24);  //Clear MODE14 and CFN14 on GPIO register B
    GPIOB_CRH &= ~(0xF << 28);  //Clear MODE15 and CFN15 on GPIO register B
    GPIOB_CRH &= ~(0xF << 16);  //Clear MODE12 and CFN12 on GPIO register B
    
    GPIOB_CRH |= (2 << 20);      //GPIO Mode13 10mhz output
    GPIOB_CRH |= (2 << 22);     //GPIO CFN13 alternate push-pull
    
    
    GPIOB_CRH |= (2 << 24);     //GPIO Mode14 10mhz output
    GPIOB_CRH |= (2 << 26);     //GPIO CFN14 alternate push-pull
    
    GPIOB_CRH |= (2 << 28);     //GPIO Mode15 10mhz output
    GPIOB_CRH |= (2 << 30);     //GPIO CFN15 alternate push-pull
    
    
    GPIOB_CRH |= (2 << 16);     //GPIO Mode12 10mhz output
    GPIOB_CRH |= (0 << 18);     //GPIO CFN12out push-pull
    
    // SPI configuration
    SPI2_CR1 = 0;       // Clear CR1 register
    
    SPI2_CR1 |= (1 << 2);        //enable master mode on SPI_CR1 
    SPI2_CR1 |= (1 << 9);        //Enable software slave management on SPI_CR1
    SPI2_CR1 |= (1 << 8);        //Internal Slave Select
    SPI2_CR1 |= (0b000 << 3);    //Baud rate 000: fPCLK/2


    SPI2_CR1 |= (1<<6); // Enable SPI

}
void delay(volatile uint32_t count)
{
    while (count--)
    {
        // Do nothing, just wait
    }
}
void SPI2_SendString(uint8_t strlen, uint8_t *pTxBuffer)
{
    GPIOB_BSRR |= (1 << 28);            //set pb12(NSS) pin to low
    
    while (strlen > 0)
    {
        while (!(SPI2_SR & 0x0002));    // Wait until transmit buffer is empty
        SPI2_DR=*pTxBuffer;             //write data byte to SPI2 data register
        while (SPI2_SR & 0x0080);       // Wait until SPI is not busy
        strlen--;
        pTxBuffer ++;
    }
    
    GPIOB_BSRR |= (1 << 12);            //set pb12(NSS) pin to high



}
void SPI2_Byte(uint8_t data)
{
        GPIOB_BSRR |= (1 << 28);        //reset PB12 pin (LOW state)
        
        while (!(SPI2_SR & 0x0002)); // Wait until transmit buffer is empty
        *((volatile uint8_t*)&SPI2_DR) = data; // Send data
        while (SPI2_SR & 0x0080); // Wait until SPI is not busy
        delay(1);
        GPIOB_BSRR |= (1 << 12);        //set high to PB12 pin
}

int main ()
{
    GPIO_Config();   
    SPI2_Config();
    
    char userData[] = "Hello World!";
    uint8_t dataLen = strlen(userData);
    while(1)
    {
        SPI2_Byte(dataLen);
        SPI2_SendString(dataLen,(uint8_t*)userData);
        delay(1000000);
        //GPIOC_ODR ^= (1<<13);
        //GPIOC_ODR ^= (1<<14);
        //GPIOC_BSRR = (1<<14);   //set high to PC 14 pin
        //GPIOC_BSRR = (1<<29);   //reset PC14 pin
        /*
        GPIOB_BSRR |= (1 << 28);
        
        while (!(SPI2_SR & 0x0002)); // Wait until transmit buffer is empty
        *((volatile uint8_t*)&SPI2_DR) = data; // Send data
        while (SPI2_SR & 0x0080); // Wait until SPI is not busy
        delay(1);
        GPIOB_BSRR |= (1 << 12);
        //GPIOB_ODR |= (0 << 12);
        delay(500000);
        GPIOC_ODR ^= (1<<13);
        */
        
    }
}