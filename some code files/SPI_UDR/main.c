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
    GPIO_Handle_t NSSPins;
    
    
    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2mhz;
    //SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OP_TYPE_PP;
    //SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OUTCONF_ALT_PP;
    
    //SCK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    GPIO_Init(&SPIPins);
    
    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
    GPIO_Init(&SPIPins);
   /* 
    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
    GPIO_Init(&SPIPins);
        */
    /*
    //NSS
    NSSPins.pGPIOx = GPIOA;
    NSSPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_2mhz;
    //NSSPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OP_TYPE_PP;
    //NSSPins.GPIO_PinConfig.GPIO_PinConf = GPIO_NO_PUPD;
    //NSSPins.GPIO_PinConfig.GPIO_PinConf = GPIO_OP_TYPE_PP;
    NSSPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
    GPIO_Init(&NSSPins);
    */
    
    //NSS
    
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
    GPIO_Init(&NSSPins);

    
    
}

void SPI1_Inits()
{
    SPI_Handle_t SPI1Handle;
    
    SPI1Handle.pSPIx = SPI1;
    SPI1Handle.SPIConf.SPI_BusConf = SPI_BUS_FD; //1
    SPI1Handle.SPIConf.SPI_DevMode = SPI_MODE_MASTER; //1
    SPI1Handle.SPIConf.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; //1
    SPI1Handle.SPIConf.SPI_DFF = SPI_DFF_8;//0
    SPI1Handle.SPIConf.SPI_CHPA = SPI_CPHA_LOW;//0
    SPI1Handle.SPIConf.SPI_CPOL = SPI_CPOL_LOW;//0
    
    SPI1Handle.SPIConf.SPI_SSM = SPI_SSM_EN; //software slave management
    SPI1Handle.SPIConf.SPI_SSI = 1;
    
    SPI_Init(&SPI1Handle);



}

void delay(volatile uint32_t iteration) {
    while (100*iteration > 0) {
        iteration--;
    }
}

void GPIO_ButtonInit()
{
    GPIO_Handle_t GPIOBtn;
    
    GPIOBtn.pGPIOx = GPIOA;
    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOBtn.GPIO_PinConfig.GPIO_PinConf = GPIO_INMODE_PUPD;
    //GPIOBtn.GPIO_PinConfig.GPIO_PinConf = GPIO_NO_PUPD;
    //GPIOBtn.GPIO_PinConfig.GPIO_PinConf = GPIO_OUTCONF_ALT_PP;

    GPIO_Init(&GPIOBtn);
}

int main()
{
    
    char userData[] = "Hello World!";
    
    
    GPIO_ButtonInit();
    
    SPI1_GPIOInits();
    
    SPI1_Inits();
    
    
    /*
        making SSOE 1 does NSS output enable
        the NSS pin is automatically managed by the hardware
        i.e when SPE=1 NSS will be pulled to low
        and NSS will be pulled to high when SPE=1
    */
    //SPI1_CR2 |= (1 << 2);
    //SPI_SSOEConfig(SPI1,ENABLE);
    
    //NSS signal internaly high avoid modf error
    SPI_SSIConfig(SPI1,ENABLE);
    while(1)
    {
        
    
        //while(! GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_3) );
        //delay(10000);
        //enable spi1 peripheral 
        SPI_PeriControl(SPI1,ENABLE);
        
        
        
        
        //first send length information
        uint8_t dataLen = strlen(userData);
        
        GPIO_WriteToOutputPinBSSR(GPIOA, 4, 0);
        
        SPI_SendData(SPI1,&dataLen,1);
        //activate slave what is connected to nss pin
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 0);
            
        SPI_SendData(SPI1,(uint8_t*)userData,strlen(userData));
        
        //nss pin high to deactivate slave what is connected to nss pin
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 1);
        while( SPI_GetFlagStatus(SPI1,SPI_BUSY_FLAG) );
        GPIO_WriteToOutputPinBSSR(GPIOA, 4, 1);
        //disable spi1 peripheral 
        //SPI_PeriControl(SPI1,DISABLE);
    }
        
    while (1)
    {
        //delay(10000);
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 0);
        //delay(100);
        //SPI_SendData(SPI1,(uint8_t*)userData,strlen(userData));
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 1);
        //activate slave what is connected to nss pin
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 0);
            
        //SPI_SendData(SPI1,(uint8_t*)userData,strlen(userData));
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 1);
        //delay(500000);

    }
    
    //return 0;
}
