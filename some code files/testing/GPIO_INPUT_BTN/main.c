#include <stdint.h>

// Define base addresses for peripherals
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800

// Define register addresses for RCC and GPIOA
#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL       (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_IDR       (*(volatile unsigned int *)(GPIOA_BASE + 0x08))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))

// Clock enable bit for GPIOA
#define RCC_APB2ENR_IOPAEN   (1 << 2)

// GPIOA configuration bits Input mode
#define GPIO_CRL_CNF2        (0b10 << 10)   // General purpose input mode (reset state) (0b00)
#define GPIO_CRL_MODE2       (0 << 8)   // Input mode (reset state) (0b00)
//GPIO Conf for output mode
#define GPIO_CRL_MODE1       (1 << 4)  // Output mode, max speed 10 MHz (0b01)
#define GPIO_CRL_CNF1        (0 << 6)  // General purpose output push-pull (0b00)

// Bit mask for PA0
#define GPIO_PIN_2           (1 << 8)

#define GPIO_PIN_2_CLEAR        ~((0xF) << 4)
#define GPIO_PIN_1_CLEAR        ~((0xF) << 8)


// Function for a simple delay
void delay(volatile uint32_t count);

int main(void)
{
    
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    // Configure PA5 as General Purpose Output Push-Pull
    GPIOA_CRL &= GPIO_PIN_2_CLEAR;       // Clear MODE5 and CNF5 bits
    GPIOA_CRL |= (GPIO_CRL_MODE1 | GPIO_CRL_CNF1); // Set MODE5 and CNF5 bits
    
    GPIOA_CRL &= GPIO_PIN_1_CLEAR;       // Clear MODE5 and CNF5 bits
    GPIOA_CRL |= (GPIO_CRL_CNF2 | GPIO_CRL_CNF2); // Set MODE5 and CNF5 bits

    uint8_t buttonState = 0;
    while (1)
    {
        // Read the state of the push button
        
        buttonState = (GPIOA_IDR & (1 << 2));
        // If button is pressed (active low), toggle LED
        if (buttonState)
        {
            // Toggle PA5
            GPIOA_ODR ^= (1 << 1);
            delay(1000000);
        }

        // Delay for debouncing and to avoid rapid multiple presses
        //delay(50000);
    }
}



void delay(volatile uint32_t count)
{
    while (count--)
    {
        // Do nothing, just wait
    }
}
