
//////////////////////////////////////////////////////////////////////////////////	 
////本程序参考正点原子直接操作寄存器程序,包括Sistick定时器和位带操作
////////////////////////////////////////////////////////////////////////////////// 
#ifndef __DELAY_H
#define __DELAY_H 			   
	
#include "stm32f10x.h"	


extern void SysTick_Init(u8 SYSCLK);	   //初始化延迟函数
extern void Delay_ms(u16 nms);			   //延时nms
extern void Delay_us(u32 nus);			   //延时nus

#endif





























