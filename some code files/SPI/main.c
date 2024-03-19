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
    SPI1Handle.SPIConf.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; //1
    SPI1Handle.SPIConf.SPI_DFF = SPI_DFF_8;//0
    SPI1Handle.SPIConf.SPI_CHPA = SPI_CPHA_LOW;//0
    SPI1Handle.SPIConf.SPI_CPOL = SPI_CPOL_LOW;//0
    
    SPI1Handle.SPIConf.SPI_SSM = SPI_SSM_DI; //software slave management
    //SPI1Handle.SPIConf.SPI_SSI = 1;
    
    SPI_Init(&SPI1Handle);



}

void delay(volatile uint32_t iteration) {
    while (100*iteration > 0) {
        iteration--;
    }
}


void GPIO_Button_Init(void)
{
    GPIO_Handle_t GPIOBtn;
        
    GPIOBtn.pGPIOx = GPIOA;
    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber       = GPIO_PIN_0;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode         = GPIO_MODE_IN;
    GPIOBtn.GPIO_PinConfig.GPIO_PinConf = GPIO_INMODE_PUPD;  //0
    GPIO_Init(&GPIOBtn);
    
}

int main()
{
    
    char userData[] = "Hello World!";
    //SPI_SendData(SPI1,(uint8_t*)userData,12);
        
        
        
    GPIO_Button_Init();

    SPI1_GPIOInits();
    
    SPI1_Inits();
    
    
    //NSS signal internaly high avoid modf error
    //SPI_SSIConfig(SPI1,ENABLE);
    
    
    //enable SSOE register
    /*
    - making SSOE 1 does NSS output enable
    - The NSS pin is automatically managed by the hardware
    - i.e when SPE=1 , NSS will be pulled to low
    - and NSS pin will be HIGH when SPE=0
    */
    SPI_SSOEConfig(SPI1,ENABLE);
    
    
    while (1)
    {
    
        while(! GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_0));
        
        delay(500);
        //enable spi2 peripheral 
        SPI_PeriControl(SPI1,ENABLE);
        
        
   
        //delay(500000);
        
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 0);
        
        
        //first send data length
        
        uint8_t datalen = strlen(userData);
        SPI_SendData(SPI1,&datalen,1);
        
        //confitm SPI is not busy
        while (SPI_GetFlagStatus(SPI1,SPI_BUSY_FLAG));
        
        SPI_PeriControl(SPI1,DISABLE);
        //GPIO_WriteToOutputPinBSSR(GPIOA, 4, 1);

    }
    //return 0;
}
