#include "include.h"

void keys_configration(void)
{
  RCC->APB2ENR|=0xf<<2;//enable GPIOA and GPIOB and GPIOD CLOCK
  GPIOA->CRH&=0x0fffffff;//PA15
  GPIOA->CRH|=0x80000000;//input with pull-push
  GPIOA->ODR|=1<<15;

  GPIOD->CRL&=0xfffff0ff;//PB3
  GPIOD->CRL|=0x00000800;//input with pull-push
  GPIOD->ODR|=1<<2;

  GPIOC->CRH&=0xfff000ff;//PC10,PC11,PC12
  GPIOC->CRH|=0x00088800;//input with pull-push
  GPIOC->ODR|=1<<10;
  GPIOC->ODR|=1<<11;
  GPIOC->ODR|=1<<12;
}


