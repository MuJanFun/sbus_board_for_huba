#ifndef __AD7705_H__
#define __AD7705_H__

#include "include.h"

#define CHANNEL_1 1
#define CHANNEL_2 2

#define SCLK_SET GPIOC->ODR|=1<<0
#define SCLK_CLR GPIOC->ODR&=~(1<<0)

#define RESET_SET GPIOC->ODR|=1<<1
#define RESET_CLR GPIOC->ODR&=~(1<<1)

#define DIN(x) (x)?(GPIOC->ODR|=1<<2):(GPIOC->ODR&=~(1<<2))

#define DOUT_STA (GPIOC->IDR&(1<<3))?1:0
#define DRDY_STA (GPIOA->IDR&(1<<0))?1:0

#define ENABLETIM2     TIM2->CR1|=0x01
#define DISENABLETIM2   TIM2->CR1&=0xfe


static void TIM2_NVIC_Configration(void);
void ad_tim2_init(u16 Arr,u16 Psc);
u16 read_ad(u8 regnum);
void write_ad(u8 dat);
void ad7705_io_configration(void);
void ad7705(u8 casenum);
void tim3_init(u16 Arr,u16 Psc);

#endif
