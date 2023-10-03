#include <stdint.h>

#define ADC_BASE_ADDR       0x40012400UL

#define ADC_CR1_OFFSET      0x04UL

#define ADC_CR1_REG_ADDR    (ADC_BASE_ADDR+ADC_CR1_OFFSET)

#define RCC_BASE_ADDR       0x40021000UL

#define RCC_APB2_ENR_OFFSET 0x18UL

#define RCC_APB2_ENR_ADDR   (RCC_BASE_ADDR+RCC_APB2_ENR_OFFSET)

int main()
{
  
  uint32_t *pAdcCr1Reg = (uint32_t*)ADC_CR1_REG_ADDR;
  uint32_t *pRccApb2Enr= (uint32_t*)RCC_APB2_ENR_ADDR;
  
  
  *pRccApb2Enr|= (1 << 9);
  *pAdcCr1Reg |= (1 << 8);

  
  for(int i = 0;i<19;i++)
   // *pAdcCr1Reg |= (1 << i);
  return 0;
}
