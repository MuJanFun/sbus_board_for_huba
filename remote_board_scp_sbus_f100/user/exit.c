#include "include.h"


/******************************************************************************* 
* Function Name  : EXTI_Configuration 
* Description    : Configration EXTI ,connect PB7 to EXTI 
* Input          : None 
* Output         : None 
* Return         : None 
*******************************************************************************/ 
void EXTI_Configuration(void) 
{ 
    EXTI_InitTypeDef EXTI_InitStructure; 

	NVIC_InitTypeDef NVIC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;	              /* 定义1个结构体变量 */

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  /* 使能AFIO时钟*/
	 
    //GPIOB7作为中断脚，配置为下拉输入	   //PB7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
    GPIO_Init(GPIOB,&GPIO_InitStructure);            
    /*connect PB7 to EXTI*/ 
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7); 
    /*Config EXTI7*/ 
    EXTI_InitStructure.EXTI_Line = EXTI_Line7; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    EXTI_Init(&EXTI_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);    
     
    /* Configure the NVIC Preemption Priority Bits*/   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 


} 











 

