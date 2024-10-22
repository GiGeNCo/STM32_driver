#include"stdint.h"

#define RCC_BASE		0x40023800
#define GPIOA_BASE		0x40020000
#define GPIOC_BASE		0x40020800


#define GPIOC_MODER		(*(volatile uint32_t *) GPIOC_BASE)
#define GPIOC_ODR		(*(volatile uint32_t *) (GPIOC_BASE + 0x14))


// Base addresses for RCC and GPIOA
#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000

// Offsets for registers
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_PUPDR     (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR       (*(volatile uint32_t *)(GPIOA_BASE + 0x10))

// Define the pin number for the button
#define BUTTON_PIN      0

void init_button() {
    // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 0);  // Set bit 0 to enable GPIOA clock
    // Set PA0 as input (MODER = 00)
    GPIOA_MODER &= ~(3 << (BUTTON_PIN * 2));  // Clear mode bits for PA0

    // Set PA0 as pull-down (PUPDR = 10)
    GPIOA_PUPDR &= ~(3 << (BUTTON_PIN * 2));  // Clear pull-up/pull-down bits for PA0
    GPIOA_PUPDR |= (2 << (BUTTON_PIN * 2));   // Set pull-down (10)
}

int read_button() {
    // Read the input data register for PA0
    return (GPIOA_IDR & (1 << BUTTON_PIN)) ? 1 : 0;
}

void delay(volatile uint32_t count) {
    while (count--) {
        // Simple delay loop
    }
}

int main(void) {
    // Initialize the button
    init_button();
    
    RCC_AHB1ENR |= (1 << 2);	//enable GPIOC
    GPIOC_MODER |= (1 << 26);	// PC13 enable output mode

    GPIOC_ODR |= (1 << 13);
    GPIOC_ODR &= ~(1 << 13);

    while (1) {
        // Check if the button is pressed
        if (read_button()) {
            // Button is pressed
            // Add your action here (e.g., toggle an LED, send a message, etc.)
            // For debugging, you might print something or toggle another GPIO
            // Example:
            // printf("Button pressed!\n");
        } else {
            // Button is not pressed
            // Add your action here
            // Example:
            // printf("Button not pressed!\n");
        }

        // Delay to debounce the button press and to observe the behavior
        delay(100000);
    }

    return 0;
}
