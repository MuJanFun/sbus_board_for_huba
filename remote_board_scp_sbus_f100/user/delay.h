
//////////////////////////////////////////////////////////////////////////////////	 
////������ο�����ԭ��ֱ�Ӳ����Ĵ�������,����Sistick��ʱ����λ������
////////////////////////////////////////////////////////////////////////////////// 
#ifndef __DELAY_H
#define __DELAY_H 			   
	
#include "stm32f10x.h"	


extern void SysTick_Init(u8 SYSCLK);	   //��ʼ���ӳٺ���
extern void Delay_ms(u16 nms);			   //��ʱnms
extern void Delay_us(u32 nus);			   //��ʱnus

#endif





























