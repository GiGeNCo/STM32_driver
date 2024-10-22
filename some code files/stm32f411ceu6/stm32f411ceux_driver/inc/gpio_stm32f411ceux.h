#include "stm32f411ceux.h"


#define OUTPUT          1
#define INPUT           0

#define LOWSPEED        0
#define MEDSPEED        1
#define FASTSPEED       2
#define HIGHSPEED       3

#define PUSH_PULL       0
#define OPEN_DRAIN      1



typedef struct
{
    uint8_t PinNumber;
    uint8_t Port;
    uint8_t IOMode;
    uint8_t Speed;
    uint8_t Type;

}GPIO_Configuration;

typedef struct 
{
    GPIO_Configuration GPIO_Conf;
    GPIO_Reg *pGPIOx;

}GPIO_Handle;



void GPIO_Init(GPIO_Handle *pGPIO);
void GPIO_Write(GPIO_Reg *pGPIO, uint8_t pinNumber, uint8_t value);




