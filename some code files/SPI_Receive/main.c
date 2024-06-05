#include <stdint.h>

// Base addresses for peripherals
#define RCC_BASE        0x40021000
#define GPIOB_BASE      0x40010C00
#define SPI2_BASE       0x40003800

// Offset addresses for registers
#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x1C))
#define GPIOB_CRL       (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_CRH       (*(volatile unsigned int *)(GPIOB_BASE + 0x04))
#define SPI2_CR1        (*(volatile unsigned int *)(SPI2_BASE + 0x00))
#define SPI2_CR2        (*(volatile unsigned int *)(SPI2_BASE + 0x04))
#define SPI2_SR         (*(volatile unsigned int *)(SPI2_BASE + 0x08))
#define SPI2_DR         (*(volatile unsigned int *)(SPI2_BASE + 0x0C))

// Macros for bit manipulation
#define BIT_SET(reg, bit)      ((reg) |= (1U << (bit)))
#define BIT_CLEAR(reg, bit)    ((reg) &= ~(1U << (bit)))

// Function prototypes
void SPI2_Init(void);
uint8_t SPI2_Receive(void);

int main(void) {
    // Initialize SPI2
    SPI2_Init();

    // Receive data
    uint8_t received_data = SPI2_Receive();

    // Loop indefinitely
    while (1) {
    }

    return 0;
}

void SPI2_Init(void) {
    // Enable clock for GPIOB and SPI2
    BIT_SET(RCC_APB2ENR, 3);  // GPIOB clock
    BIT_SET(RCC_APB1ENR, 14); // SPI2 clock

    // Configure GPIOB for SPI2
    // PB13 (SPI2_SCK), PB14 (SPI2_MISO), PB15 (SPI2_MOSI)
    GPIOB_CRH &= ~(0xFFF << 20); // Clear current settings
    GPIOB_CRH |=  (0xB4B << 20); // Alternate function push-pull for SCK and MOSI, input floating for MISO

    // Configure SPI2
    SPI2_CR1 = 0;
    SPI2_CR1 |= (1 << 2);  // Master selection
    SPI2_CR1 |= (1 << 9);  // Software slave management
    SPI2_CR1 |= (1 << 8);  // Internal slave select
    //SPI2_CR1 |= (1 << 6);  // SPI enable
    SPI2_CR1 |= (1 << 11); // 8-bit data frame format


    // Set baud rate to fPCLK/16
    SPI2_CR1 |= (3 << 3);

    // Enable SPI2
    SPI2_CR1 |= (1 << 6);
}

uint8_t SPI2_Receive(void) {
    // Wait until data is received
    while (!(SPI2_SR & (1 << 0))); // Wait for RXNE bit to be set

    // Read data from SPI2 data register
    return (uint8_t)SPI2_DR;
}
