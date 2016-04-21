
#include "include.h"
void RCC_Configuration(void);
void BSP_init(void)
{  
  RCC_Configuration();
	SysTick_Init(36);
}
void RCC_Configuration(void)
{
  RCC_PLLConfig(RCC_PLLSource_HSE_Div2,RCC_PLLMul_3);
	RCC_PLLCmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}





