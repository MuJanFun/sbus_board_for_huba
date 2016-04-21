
//////////////////////////////////////////////////////////////////////////////////	 
//������ο�����ԭ��ֱ�Ӳ����Ĵ�������,����Sistick��ʱ��
//////////////////////////////////////////////////////////////////////////////////	

#include"include.h"

static u8  fac_us=0;								//us��ʱ������
static u16 fac_ms=0;								//ms��ʱ������

/********************************************
������delay_init
���ܣ���ʼ���ӳٺ���
������SYSCLK:ϵͳʱ��
���أ���
********************************************/
void SysTick_Init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;					 //bit2���,ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		  					 // SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
	fac_ms=(u16)fac_us*1000;
}

/********************************************
������delay_ms
���ܣ���ʱnms
������nms:ms����Ŀ
���أ���
ע��SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=0xffffff*8*1000/SYSCLK��
	SYSCLK��λΪHz,nms��λΪms����72M������,nms<=1864��
********************************************/
void Delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
 		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}   

/********************************************
������delay_us
���ܣ���ʱnus
������nus:us����Ŀ
���أ���
********************************************/		    								   
void Delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
































