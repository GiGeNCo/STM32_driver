#include "stm32f103c8xx.h"
#include "string.h"

/*
*       SPI2
*       PA4 --> NSS
*       PA5 --> SCK
*       PA6 --> MISO
*       PA7 --> MOSI
*       ALF Function    5
*/
void SPI1_GPIOInits()
{
    GPIO_Handle_t SPIPins;
    
    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2mhz;
    //SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OP_TYPE_PP;
    //SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OUTCONF_ALT_PP;
    
    //SCK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 5;
    GPIO_Init(&SPIPins);
    
    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 7;
    GPIO_Init(&SPIPins);
   /* 
    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
    GPIO_Init(&SPIPins);
        */
    //NSS
    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2mhz;
    //SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OP_TYPE_PP;
    //SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 4;
    GPIO_Init(&SPIPins);
    
    

    
    
}

void SPI1_Inits()
{
    SPI_Handle_t SPI1Handle;
    
    SPI1Handle.pSPIx = SPI1;
    //SPI1Handle.SPIConf.SPI_BusConf = SPI_BUS_FD; //1
    SPI1Handle.SPIConf.SPI_DevMode = SPI_MODE_MASTER; //1
    SPI1Handle.SPIConf.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV256; //1
    SPI1Handle.SPIConf.SPI_DFF = SPI_DFF_8;//0
    SPI1Handle.SPIConf.SPI_CHPA = SPI_CPHA_LOW;//0
    SPI1Handle.SPIConf.SPI_CPOL = SPI_CPOL_LOW;//0
    
    SPI1Handle.SPIConf.SPI_SSM = 1; //software slave management
    SPI1Handle.SPIConf.SPI_SSI = 1;
    
    SPI_Init(&SPI1Handle);



}

void delay(volatile uint32_t iteration) {
    while (100*iteration > 0) {
        iteration--;
    }
}

int main()
{
    
    SPI1_GPIOInits();
    
    SPI1_Inits();
    
    
    //NSS signal internaly high avoid modf error
    //SPI_SSIConfig(SPI1,ENABLE);
    
    //enable spi2 peripheral 
    SPI_PeriControl(SPI1,ENABLE);
    
    
    char userData[] = "Hello World!";
    //SPI_SendData(SPI1,(uint8_t*)userData,12);
    while (1)
    {
        delay(10000);
        SPI_SendData(SPI1,(uint8_t*)userData,strlen(userData));

    }
    //return 0;
}
