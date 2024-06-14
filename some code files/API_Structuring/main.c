#include "stm32f103c8xx.h"
#include "string.h"

void delay(uint64_t value)
{
    while(value--);
}

int main()
{
    GPIO_Handler pin;
    pin.pGPIOx = GPIOC;
    pin.GPIO_Configuration.GPIO_PinNumber = 14;
    pin.GPIO_Configuration.GPIO_Mode    = OUTPUT_2MHZ;
    pin.GPIO_Configuration.GPIO_Cfn     = GPIO_OUT_PUSH_PULL;
      
    Enable_RCC(GPIOC);
    GPIO_Init(&pin);
    
    GPIO_Handler btnPin;
    
    btnPin.pGPIOx = GPIOC;
    btnPin.GPIO_Configuration.GPIO_PinNumber = 15;
    btnPin.GPIO_Configuration.GPIO_Mode = INPUT;
    btnPin.GPIO_Configuration.GPIO_Cfn = GPIO_IN_PULL_UP_PULL_DOWN;
    
    GPIO_Init(&btnPin);
    
    GPIO_Write(btnPin.pGPIOx,15,HIGH);
    
    //************************  SPI2 
    
    SPI_Handler spi2;
    spi2.pSPIx = SPI2;
    spi2.SPIConf.SPI_Mode = SPI_MODE_MASTER;
    spi2.SPIConf.SPI_Speed = SPI_SPEED_DIV16;
    spi2.SPIConf.SPI_DFF = SPI_DFF_8;
    spi2.SPIConf.SPI_SSM = SPI_SSM_EN;
    spi2.SPIConf.SPI_SSI = SPI_SSI_EN;
    spi2.SPIConf.SPI_CHPA = SPI_CPOL_LOW;
    spi2.SPIConf.SPI_CPOL = SPI_CPOL_LOW;
    
    RCC_ENABLE_SPI(spi2.pSPIx);
    
    
    SPI_Init(&spi2);
    
    //configure NSS pin
    GPIO_Handler spipin;
    spipin.pGPIOx = GPIOB;
    spipin.GPIO_Configuration.GPIO_PinNumber = 12;
    spipin.GPIO_Configuration.GPIO_Mode    = OUTPUT_2MHZ;
    spipin.GPIO_Configuration.GPIO_Cfn     = GPIO_OUT_PUSH_PULL;
      
    Enable_RCC(spipin.pGPIOx);
    GPIO_Init(&spipin);
    GPIO_Write(spipin.pGPIOx,12,HIGH);
    
    //configure SPI clock pin
    spipin.pGPIOx = GPIOB;
    spipin.GPIO_Configuration.GPIO_PinNumber = 13;
    spipin.GPIO_Configuration.GPIO_Mode    = OUTPUT_2MHZ;
    spipin.GPIO_Configuration.GPIO_Cfn     = GPIO_ALT_OUT_PUSH_PULL;
    GPIO_Init(&spipin);
    
    spipin.GPIO_Configuration.GPIO_PinNumber = 14;
    GPIO_Init(&spipin);
    
    spipin.GPIO_Configuration.GPIO_PinNumber = 15;
    GPIO_Init(&spipin);
    
    char userData[] = "Hello World!";
    uint8_t datalen = strlen(userData);
    
    while(1)
    {
        GPIO_Write(spipin.pGPIOx,12,LOW);
        //SPI2_Byte(spi2.pSPIx,'c');
        SPI_SendData(spi2.pSPIx, (uint8_t *) userData, datalen);
        delay(5);
        GPIO_Write(spipin.pGPIOx,12,HIGH);
        //GPIO_Write(pin.pGPIOx,14,HIGH);
        //delay(1000000);
        //GPIO_Write(pin.pGPIOx,14,LOW);
        //delay(1000000);
        if(GPIO_Read(btnPin.pGPIOx,15) == LOW)
        {
            GPIO_Write(pin.pGPIOx,14,HIGH);
        }
        else if(GPIO_Read(btnPin.pGPIOx,15) == HIGH)
        {
            GPIO_Write(pin.pGPIOx,14,LOW);
        }
        
        
    }
}
