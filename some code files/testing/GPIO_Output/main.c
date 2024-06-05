#include <stdint.h>

// Define base addresses for peripherals
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800

// Define register addresses for RCC and GPIOA
#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL       (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))

// Clock enable bit for GPIOA
#define RCC_APB2ENR_IOPAEN   (1 << 2)

// GPIOA configuration bits
#define GPIO_CRL_MODE5       (3 << 20)  // Output mode, max speed 50 MHz (0b11)
#define GPIO_CRL_CNF5        (0 << 22)  // General purpose output push-pull (0b00)

void delay(volatile uint32_t count);

int main(void)
{
    // Enable clock for GPIOA
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure PA5 as General Purpose Output Push-Pull
    GPIOA_CRL &= ~((0xF) << 20);       // Clear MODE5 and CNF5 bits
    GPIOA_CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_CNF5); // Set MODE5 and CNF5 bits

    while (1)
    {
        // Toggle PA5
        GPIOA_ODR ^= (1 << 5);

        // Delay
        delay(2000000);
    }
}

void delay(volatile uint32_t count)
{
    while (count--)
    {
        // Do nothing, just wait
    }
}
