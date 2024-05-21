#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800
#define SPI1_BASE       0x40013000

#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL       (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define SPI1_CR1        (*(volatile unsigned int *)(SPI1_BASE + 0x00))
#define SPI1_SR         (*(volatile unsigned int *)(SPI1_BASE + 0x08))
#define SPI1_DR         (*(volatile unsigned int *)(SPI1_BASE + 0x0C))

// RCC bits
#define RCC_APB2ENR_IOPAEN   (1 << 2)
#define RCC_APB2ENR_SPI1EN   (1 << 12)

// GPIO bits
#define GPIO_CRL_MODE5       (1 << 20)
#define GPIO_CRL_CNF5_1      (1 << 21)
#define GPIO_CRL_MODE6       (1 << 24)
#define GPIO_CRL_CNF6_1      (1 << 25)
#define GPIO_CRL_MODE7       (1 << 28)
#define GPIO_CRL_CNF7_1      (1 << 29)

// SPI bits
#define SPI_CR1_MSTR         (1 << 2)
#define SPI_CR1_SSM          (1 << 9)
#define SPI_CR1_SSI          (1 << 8)
#define SPI_CR1_SPE          (1 << 6)
#define SPI_CR1_BR_0         (1 << 3)
#define SPI_CR1_BR_1         (1 << 4)
#define SPI_SR_TXE           (1 << 1)
#define SPI_SR_BSY           (1 << 7)

void SPI1_Init(void);
void SPI1_SendData(uint8_t data);

int main(void)
{
    // Initialize SPI1
    SPI1_Init();

    // Send data byte
    SPI1_SendData(0x55); // Example data byte

    while (1)
    {
        // Loop indefinitely
    }
}

void SPI1_Init(void)
{
    // Enable clocks for GPIOA and SPI1
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
    RCC_APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable SPI1 clock

    // Configure PA5, PA6, and PA7 as Alternate Function Push-Pull
    GPIOA_CRL &= ~(0xF << 20); // Clear MODE5 and CNF5
    GPIOA_CRL &= ~(0xF << 24); // Clear MODE6 and CNF6
    GPIOA_CRL &= ~(0xF << 28); // Clear MODE7 and CNF7

    GPIOA_CRL |= (0xB << 20); // PA5 (SCK) as AF_PP
    GPIOA_CRL |= (0xB << 24); // PA6 (MISO) as AF_PP
    GPIOA_CRL |= (0xB << 28); // PA7 (MOSI) as AF_PP

    // Configure SPI1
    SPI1_CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_BR_1; // Master mode, Baud rate = Fpclk/8, Software slave management

    SPI1_CR1 |= SPI_CR1_SPE; // Enable SPI
}

void SPI1_SendData(uint8_t data)
{
    // Wait until TXE (Transmit buffer empty) flag is set
    while (!(SPI1_SR & SPI_SR_TXE));

    // Send data
    SPI1_DR = data;

    // Wait until the transmission is complete (optional)
    while (SPI1_SR & SPI_SR_BSY);
}
