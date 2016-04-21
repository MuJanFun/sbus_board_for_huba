#include "include.h"

DMA_InitTypeDef  DMA_InitStructure;
DMA_InitTypeDef  DMA_InitStructure1;
u8 DMABUF1[15];

u8 databuf;
/* ----------- */
 u8 sbus_buffer[50];

__IO u8 sbus_moved = 0;

u8 frame[25];

/* ----------- */
extern TxCpy fsac;
u8 DMABUF[15]={'A','T','+',':',0,0,0,0,0,0,0,0,'e','n','d'};
#if 1
#pragma import(__use_no_semihosting)             
             
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif
extern __IO char flag_tac;
void USART1_IRQHandler(void)
{
	char c;
	if(USART1->SR&(1<<4))
	{
		c = USART1->DR;
	  (void)c;
//	  DMA1_Channel5->CCR&=~(0x1);
		 memcpy((void*)frame,(void *)sbus_buffer,25);
//	  DMA1_Channel5->CCR|=1;
	}
	DMA1_Channel5->CCR&=~(0x1);
	DMA1_Channel5->CNDTR = 50;
	DMA1_Channel5->CCR|=1;
}

void sbus_init(void)
{
  GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	DMA_InitTypeDef dma;
	NVIC_InitTypeDef nvic;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1|RCC_AHBPeriph_DMA2,ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Pin = GPIO_Pin_9;
	
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&gpio);
	
	/* usart config */
  usart.USART_BaudRate = 100000;
	usart.USART_Parity = USART_Parity_Even;
	usart.USART_StopBits = USART_StopBits_2;
	usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	usart.USART_WordLength = USART_WordLength_9b;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&usart);
	
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
	
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
	
	/*dma config*/
	dma.DMA_BufferSize = 50;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_M2M = DMA_MemoryInc_Disable;
	dma.DMA_MemoryBaseAddr = (uint32_t)&sbus_buffer;
	dma.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Priority = DMA_Priority_High;
	
	DMA_Init(DMA1_Channel5,&dma);
	DMA_Cmd(DMA1_Channel5,ENABLE);
	
	/* NVIC */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}


void usart_send_init(void)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Pin = GPIO_Pin_2;
	
	GPIO_Init(GPIOA,&gpio);/* USART2 TX PA2 */
	
	usart.USART_BaudRate = 115200;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Mode = USART_Mode_Tx;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART2,&usart);

	USART_Cmd(USART2,ENABLE);
}


 
void RCC_Configuration1(void)
{
    ErrorStatus HSEStartUpStatus;

    //使能外部晶振
    RCC_HSEConfig(RCC_HSE_ON);
    //等待外部晶振稳定
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    //如果外部晶振启动成功，则进行下一步操作
    if(HSEStartUpStatus==SUCCESS)
    {
        //设置HCLK（AHB时钟）=SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        //PCLK1(APB1) = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);

        //PCLK2(APB2) = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        
 
        RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_3);
        //启动PLL
        RCC_PLLCmd(ENABLE);
        //等待PLL稳定
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        //系统时钟SYSCLK来自PLL输出
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //切换时钟后等待系统时钟稳定
        while(RCC_GetSYSCLKSource()!=0x08);  
     }

  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	  //重映射时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	  //GPIOC 时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE); //USART3时钟
}
 
 
 
 
 
  

