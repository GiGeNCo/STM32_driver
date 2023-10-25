#include "stm32f103c8xx.h"
#include "stm32f103c8xx.h_gpio_driver.h"




void delay()
{
    uint64_t counter = 350000;
    while(counter--);
}
int main()
{
    
    //uint32_t *pRccApb2Enr = (uint32_t)RCC_APB2_ENR_ADDR;
    //uint32_t *pGpioPortCnfr = (uint32_t)GPIO_PORT_CNFR_ADDR;
    //GPIO_Handle_t *pGpioHandle;
    //*pRccApb2Enr |= (1<<4);
    GPIO_Handle_t GpioLed;
    GpioLed.pGPIOx = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_50mhz;  //1 in reference manual is output mode
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTCONF_PP; //2 in reference manual is push pull mode
    
    
    GPIO_PeriClockControll(GPIOC,ENABLE); //enable is macro and value is 1
    GPIO_Init(&GpioLed);
    
    while(1)
    {
        GPIO_TogglePin(GPIOC,13);
        delay();
        
    }
    
    
  //return 0;
}
