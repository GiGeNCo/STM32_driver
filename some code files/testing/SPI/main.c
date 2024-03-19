#include "stdint.h"


#define RCC_BASE            0x40021000
#define GPIOA_BASE          0x40010800
#define SPI1_BASE           0x40013000

#define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x18))

#define GPIOA_CRL           (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define SPI1_CR1            (*(volatile uint32_t*)(SPI1_BASE + 0x00))
#define SPI1_DR             (*(volatile uint32_t*)(SPI1_BASE + 0x0C))
#define SPI1_SR             (*(volatile uint32_t*)(SPI1_BASE + 0x08))
#define GPIOA_BSRR          (*(volatile uint32_t*)(GPIOA_BASE + 0x10))

#define SS_PIN              (1 << 4) // Assuming PA4 is used for SS

void delay(volatile uint32_t iteration) {
    while (iteration > 0) {
        iteration--;
    }
}

void SPI1_Init(void) {
    // Enable clock for GPIOA and SPI1
    RCC_APB2ENR |= 0x00000004;
    RCC_APB2ENR |= 0x00001000;

    // Configure PA5 (SCK), PA6 (MISO), PA7 (MOSI) as alternate function push-pull
    GPIOA_CRL &= 0x000FFFFF;
    GPIOA_CRL |= 0xB4B00000;

    // Configure PA4 (SS) as output push-pull
    GPIOA_CRL &= 0xFFF0FFFF;
    GPIOA_CRL |= 0x00030000;

    // SPI configuration
    SPI1_CR1 = 0;       // Clear CR1 register
    //SPI1_CR1 |= 0x0007; // Set baud rate (you may need to adjust this)
    SPI1_CR1 = 0b0000001100111100;      // Master mode, SSM=1, SSI=1 
    SPI1_CR1 |= 0x0040; // Enable SPI
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

int main(void) {
    SPI1_Init();

    uint8_t sendData = 65; // Data to send

    while (1) {
        
        SPI1_SendByte(sendData);
        
        sendData++;
        if (sendData >90)
        {
            sendData = 65;
        }
        //delay(100); // Delay between sending data (adjust as needed)
    }
}
