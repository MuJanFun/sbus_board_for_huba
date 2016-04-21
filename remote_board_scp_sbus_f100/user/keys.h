#ifndef __KEYS_H__
#define __KEYS_H__


#define NEWPROJ_STA      (GPIOD->IDR&(1<<2))?1:0
#define STAGE_ONE_STA    (GPIOC->IDR&(1<<12))?1:0
#define STAGE_TWO_STA    (GPIOC->IDR&(1<<11))?1:0
#define STAGE_THREE_STA  (GPIOC->IDR&(1<<10))?1:0
#define DATA_SHIFT_STA   (GPIOA->IDR&(1<<15))?1:0


void keys_configration(void);

#endif


