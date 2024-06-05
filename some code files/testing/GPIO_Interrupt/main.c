#include <stdint.h>

// Define register addresses
#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000
#define EXTI_BASE       0x40010400
#define AFIO_BASE       0x40010000
#define NVIC_ISER_BASE  0xE000E100

#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_IDR       (*(volatile uint32_t *)(GPIOC_BASE + 0x08))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define EXTI_IMR        (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_FTSR       (*(volatile uint32_t *)(EXTI_BASE + 0x0C))
#define EXTI_PR         (*(volatile uint32_t *)(EXTI_BASE + 0x14))
#define AFIO_EXTICR4    (*(volatile uint32_t *)(AFIO_BASE + 0x14))
#define NVIC_ISER1      (*(volatile uint32_t *)(NVIC_ISER_BASE + 0x04))

// Function prototypes
void EXTI15_10_IRQHandler(void);
void delay(uint32_t count);

int main(void)
{
    // Enable clock for GPIOC and AFIO
    RCC_APB2ENR |= (1 << 4);  // Enable GPIOC clock
    RCC_APB2ENR |= (1 << 0);  // Enable AFIO clock

    // Configure PC15 as input
    GPIOC_CRH &= ~(0xF << 28); // Clear CNF and MODE bits for PC15
    GPIOC_CRH |= (0x8 << 28);  // Set CNF bits to input with pull-up/pull-down
    
    // Configure PC14 as OUTPUT
    GPIOC_CRH &= ~(0xF << 24); // Clear CNF and MODE bits for PC15
    GPIOC_CRH |= (0b0001 << 24);  // Set CNF bits to input with pull-up/pull-down

    // Enable EXTI line for PC15
    AFIO_EXTICR4 &= ~(0xF << 12); // Clear EXTI15 configuration
    AFIO_EXTICR4 |= (0x2 << 12);  // Set EXTI15 to be triggered by PC15

    // Configure EXTI line 15 to trigger on falling edge
    EXTI_IMR |= (1 << 15);   // Unmask EXTI line 15
    EXTI_FTSR |= (1 << 15);  // Trigger on falling edge

    // Enable EXTI15_10 interrupt in NVIC
    NVIC_ISER1 |= (1 << 8);  // Enable interrupt for EXTI15_10 (position 40-32 = 8)
    
    
    GPIOC_ODR ^= (1 << 15);

    while (1)
    {
        // Main loop
    }
}

// Interrupt handler for EXTI line [15:10]
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_PR & (1 << 15))  // Check if the interrupt was generated by PC15
    {
        // Clear the interrupt pending bit
        EXTI_PR |= (1 << 15);

        // Handle the button press event (toggle LED, etc.)
        // For demonstration, we will just toggle an LED connected to PC13

        // Assuming an LED is connected to PC13
        GPIOC_ODR ^= (1 << 14); // Toggle PC13
    }
}

// Simple delay function
void delay(uint32_t count)
{
    while (count--) ;
}
