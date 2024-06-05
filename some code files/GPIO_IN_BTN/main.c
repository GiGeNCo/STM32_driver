#include <stdint.h>

#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000

#define APB2_ENR                (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOC_CRH               (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_IDR               (*(volatile unsigned int *)(GPIOC_BASE + 0x08))
#define GPIOC_BSSR              (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_ODR               (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

void GPIO_Init()
{

    APB2_ENR |= (1<<4); //enable APB2 for GPIOB
    
    
    GPIOC_CRH &= ~(0xF << 28);          //clear mode and cnf bits for PC15
    
    GPIOC_CRH &= ~(0xF << 24);          //Clear mode and cnf bits for pc14
    
    GPIOC_CRH |= (0b1000 << 28);        //chose input mode for PC14
    
    GPIOC_CRH |= (0b0001 << 24);        //output mode 10 mhz
    
    
    // Enable pull-up by setting PC15 in ODR
    GPIOC_ODR |= (1 << 15);


}
void delay()
{
    for(uint32_t i= 0; i<100000; i++);
}

int main()
{
    GPIO_Init();
    
    uint8_t btnState = 0;
    
    
    while (1)
    {
    
        btnState = ((GPIOC_IDR >> 15) & 1);
        
        if(!btnState)
        {
            //GPIOC_BSSR |= (1<<14);
            //GPIOC_ODR |= (1<<14);
            GPIOC_ODR ^= (1<<14);
        }
        else 
        {
            //GPIOC_BSSR |= (1<<30);
            //GPIOC_ODR &= ~(1<<14);
        }
        //delay();
        
    
    }
}


