#include "stdint.h"
#include "string.h"
/*
*       SPI2
*       PA4 --> NSS
*       PA5 --> SCK
*       PA6 --> MISO
*       PA7 --> MOSI
*       ALF Function    5
*/

#define RCC_BASE            0x40021000
#define GPIOA_BASE          0x40010800
#define SPI1_BASE           0x40013000

#define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x18))

#define GPIOA_CRL           (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define SPI1_CR1            (*(volatile uint32_t*)(SPI1_BASE + 0x00))
#define SPI1_CR2            (*(volatile uint32_t*)(SPI1_BASE + 0x04))
#define SPI1_DR             (*(volatile uint32_t*)(SPI1_BASE + 0x0C))
#define SPI1_SR             (*(volatile uint32_t*)(SPI1_BASE + 0x08))
#define GPIOA_BSRR          (*(volatile uint32_t*)(GPIOA_BASE + 0x10))

#define SS_PIN              (1 << 4) // Assuming PA4 is used for SS


#define SPI_SR_TXE           (1 << 1)
#define SPI_SR_BSY           (1 << 7)

void delay(volatile uint32_t iteration) {
    while (iteration > 0) {
        iteration--;
    }
}

void SPI1_Init(void) {
    // Enable clock for GPIOA and SPI1
    //RCC_APB2ENR |= 0x00000004;
    //RCC_APB2ENR |= 0x00001000;
    RCC_APB2ENR |= (1<<2);      // Enable IOPA on RCC_APB2ENR
    RCC_APB2ENR |= (1<<12);     // Enable SPI1 on RCC_APB2ENR

    // Configure PA5 (SCK), PA6 (MISO), PA7 (MOSI) as alternate function push-pull
    
    //GPIOA_CRL &= 0x000FFFFF;
    //GPIOA_CRL |= 0xB4B00000;
    GPIOA_CRL &= ~(0xF << 20);  //Clear MODE5 and CFN5 on GPIO register A
    GPIOA_CRL &= ~(0xF << 28);  //Clear MODE7 and CFN7 on GPIO register A
    GPIOA_CRL &= ~(0xF << 24);  //Clear MODE6 and CFN6 on GPIO register A
    
    GPIOA_CRL |= (1 << 21);     //GPIO Mode5 2mhz output
    GPIOA_CRL |= (1 << 23);     //GPIO CFN5 alternate push-pull
    
    GPIOA_CRL |= (1 << 25);     //GPIO Mode6 2mhz output
    GPIOA_CRL |= (1 << 27);     //GPIO CFN6 alternate push-pull
    
    GPIOA_CRL |= (1 << 29);     //GPIO Mode7 2mhz output
    GPIOA_CRL |= (1 << 31);     //GPIO CFN7 alternate push-pull
    
    GPIOA_CRL |= (1 << 16);     //GPIO Mode4 2mhz output
    GPIOA_CRL |= (0b00 << 18);  //GPIO CFN4 out push-pull
    
    
    // Configure PA4 (SS) as output push-pull
    //GPIOA_CRL &= 0xFFF0FFFF;
    //GPIOA_CRL |= 0x00030000;

    // SPI configuration
    SPI1_CR1 = 0;       // Clear CR1 register
    
    // SPI bits
    //SPI1_CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_BR_1; // Master mode, Baud rate = Fpclk/8, Software slave management
    SPI1_CR1 |= (1 << 2);        //enable master mode on SPI_CR1 
    SPI1_CR1 |= (1 << 9);        //Enable software slave management on SPI_CR1
    SPI1_CR1 |= (1 << 8);        //Internal Slave Select
    SPI1_CR1 |= (0b000 << 3);    //Baud rate 000: fPCLK/2
 
    
    //SPI1_CR1 |= 0x0007; // Set baud rate (you may need to adjust this)
    //SPI1_CR1 = 0b0000001100111100;      // Master mode, SSM=1, SSI=1 
    
    
    SPI1_CR1 |= (1<<6); // Enable SPI
}

void SPI1_EnableSS(void) {
    GPIOA_BSRR |= (1 << 20); // Set SS pin (PA4) to low (enable)
}

void SPI1_DisableSS(void) {
    GPIOA_BSRR |= (1 << 4); // Set SS pin (PA4) to high (disable)
}

void SPI1_SendByte(uint8_t data) {
    SPI1_EnableSS(); // Enable Slave Select before sending data

    while (!(SPI1_SR & 0x0002)); // Wait until transmit buffer is empty
    *((volatile uint8_t*)&SPI1_DR) = data; // Send data
    while (SPI1_SR & 0x0080); // Wait until SPI is not busy

    SPI1_DisableSS(); // Disable Slave Select after sending data
}

void SPI1_SendData(uint8_t data);
void SPI1_SendString(uint8_t *pTxBuffer, uint32_t len);

int main(void) {
    SPI1_Init();

    
    /*
        making SSOE 1 does NSS output enable
        the NSS pin is automatically managed by the hardware
        i.e when SPE=1 NSS will be pulled to low
        and NSS will be pulled to high when SPE=1
    */
    //SPI1_CR2 |= (1 << 2);
    
    char userData[] = "Hello World!";
     
    //first send lenght information
    uint8_t dataLen = strlen(userData);
    //dataLen
    

    while (1) {
        
        SPI1_SendByte(dataLen);
        
        GPIOA_BSRR |= (1 << 20);
        SPI1_SendString((uint8_t*)userData, dataLen);
        
        GPIOA_BSRR |= (1 << 4);

        delay(667466); // Delay between sending data (adjust as needed)
    }
}

void SPI1_SendData(uint8_t data)
{
    // Wait until TXE (Transmit buffer empty) flag is set
    while (!(SPI1_SR & SPI_SR_TXE));

    // Send data
    SPI1_DR = data;

    // Wait until the transmission is complete
    while (SPI1_SR & SPI_SR_BSY);
}

void SPI1_SendString(uint8_t *pTxBuffer, uint32_t len)
{

    while (len > 0)
    {   
        // 1 - load the data into the DR
        SPI1_SendData(*pTxBuffer);
        //SPI1_SendByte(*pTxBuffer);
        len--;
        pTxBuffer ++;
    }

 
}
