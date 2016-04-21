#include "include.h"

__IO u16 vcounter;
__IO u16 icounter;
__IO u8 timeupdataflag=0;
__IO u16 freqbuf;
__IO u8  trytime=0;
__IO u8 press_public;
extern TxCpy fsac;
float bats;
extern __IO u16 freq;
const char ReadRTC[6]={0xa5,0x5a,0x03,0x81,0x20,0x10};


void ad7705_io_configration(void)
{
  RCC->APB2ENR|=1<<4; //enable gpioc clock

  //PC0(sclk),PC1(reset),PC2(DIN) OutPut，PC3(DOUT)，InPut
  GPIOC->CRL&=0xffff0000;
  GPIOC->CRL|=0x00008333;
  GPIOC->ODR|=1<<3;
  RCC->APB2ENR|=1<<2; //enable gpioa clock

  //PA0(/DRDY) InPut
  GPIOA->CRL&=0xfffffff0;
  GPIOA->CRL|=0x00000008;
}


void write_ad(u8 dat)
{
  u8 i;
  SCLK_SET;
  for(i=0;i<8;i++)
  {
  	SCLK_CLR;
	Delay_us(10);
  	DIN(((dat<<i)&0x80));
  	SCLK_SET;
	Delay_us(10);
  }
  SCLK_SET;
}


u16 read_ad(u8 regnum)
{
  u8 i;
  u16 datt=0;
  u16 sta=0;
 SCLK_SET;
 for(i=0;i<regnum;i++)
 {
   SCLK_CLR;
   Delay_us(10);
   sta=DOUT_STA;
   datt=(datt<<1)+sta;
   SCLK_SET;
   Delay_us(10);
 }
 return datt; 
}

void ad7705(u8 casenum)
{
  
  switch(casenum)
     {
	  case 1:  //setp1  Ad复位
	    
		 RESET_CLR;  //reset信号有效
         Delay_ms(10);  //延时10ms
         RESET_SET;  //reset信号无效
         break;
		
	  case 2:  //setp2  AD通道一初始化及1倍增益校准
	    
		 write_ad(0x20);//写通信寄存器（00100000）必须（0）、时钟寄存器（010）、写（0）、正常工作模式（0）、通道一（00）
         write_ad(0x04);//写时钟寄存器（00000010）必须（000）、主时钟关闭（0）、时钟不分频（0）、2.4576（1）、50HZ输出（00）
         write_ad(0x10);//写通信寄存器（00010000）必须（0）、设置寄存器（001）、写（0）、正常工作模式（0）、通道一（00）
         write_ad(0x40);//写设置寄存器（01000100）自校准（01）、1倍增益（000）、双极性（0）、非缓冲（0）、工作状态（0）

		 write_ad(0x18);//写通信寄存器（00010000）必须（0）、设置寄存器（001）、读（1）、正常工作模式（0）、通道一（00）
		 //while(DRDY_STA);
		 //adset=read_ad(8);



		 Delay_ms(40); //延时40ms
	     break;
		
	  case 3:  //空操作  延时
        
		  //Send_Dat();
		 //twohundredusdelay(200);  //延时40ms
		 break;
		
	  case 4:  //空操作  延时
        
		Delay_ms(60);//延时40ms 
		press_public=(u16)((float)(vcounter-0x8000)*1.446)/10;
		/*
		NoUsartDMAEnable(&fsac,press_p,(u16)((float)press_public/10*6.6));
		
		//NoUsartDMAEnable(&fsac,press,((float)(vcounter-0x8000)*1.446));
		if(vcounter>=0x8000)

		NoUsartDMAEnable(&fsac,press,(u16)((float)(vcounter-0x8000)*1.446));
		
		else 
		NoUsartDMAEnable(&fsac,press,0xffff-(u16)((float)(0x8000-vcounter)*1.446));
		*/ 
		 break;
		
	  case 5:  //step3  AD通道一1倍增益正常测量
	    
	     write_ad(0x10);//写通信寄存器（00010000）必须（0）、设置寄存器（001）、写（0）、正常工作模式（0）、通道一（00）
         write_ad(0x00);//写设置寄存器（00000100）正常工作（00）、1倍增益（000）、双极性（0）、非缓冲（0）、工作状态（0）
         break;
 	    
      case 6:  //step4：读取AD通道一数值，修改增益并校准n倍增益
	    
	
	     while(DRDY_STA);
		 if(DRDY_STA==0)///d/r/a/y/Y为低电平数据可用
           {
            write_ad(0x38);//写通信寄存器（00111000）必须（0）、数据寄存器（011）、读（1）、正常工作模式（0）、通道一（00）
            vcounter=read_ad(16); //读数据寄存器  
           }           
          Delay_ms(40);  //延时40ms
		  break;   
		
	  case 7://Step9：AD通道二初始化及1倍增益校准
        
	     write_ad(0x11);//写通信寄存器（00010001）必须（0）、设置寄存器（001）、写（0）、正常工作模式（0）、通道二（01）
         write_ad(0x44);//写设置寄存器（01000100）自校准（01）、1倍增益（000）、单极性（1）、非缓冲（0）、工作状态（0）
         Delay_ms(40);  //延时40ms
         break;
	     
	  case 8:    //空操作  延时
          
	 	   Delay_ms(60); //延时40ms
		   bats=(float)icounter/65536*0.99*9.25;
		   if(bats<=7.4) NoUsartDMAEnable(&fsac,battery,0); 
		   if((bats>7.4)&&(bats<=7.7)) NoUsartDMAEnable(&fsac,battery,1); 
		   if((bats>7.7)&&(bats<=7.8)) NoUsartDMAEnable(&fsac,battery,2); 
		   if((bats>7.8)&&(bats<=7.9)) NoUsartDMAEnable(&fsac,battery,3);  
		   if(bats>7.9) NoUsartDMAEnable(&fsac,battery,4); 
	  	   break;
	        
        case 9:  //空操作  延时
          
		    Delay_ms(40);  //延时40ms
			printf((const char *)ReadRTC);
		   break;
	        
	    case 10://Step10：AD通道二1倍增益正常测量
          
		   write_ad(0x11);//写通信寄存器（00010001）必须（0）、设置寄存器（001）、写（0）、正常工作模式（0）、通道二（01）
           write_ad(0x04);//写设置寄存器（00000100）正常工作（00）、1倍增益（000）、单极性（1）、非缓冲（0）、工作状态（0）
           break;
 	      
        case 11://Step11：读取通道二测量值
           
		   
	       while(DRDY_STA); 
	        if(DRDY_STA==0)
	         {
		      write_ad(0x39);//写通信寄存器（00111001）必须（0）、数据寄存器（011）、读（1）、正常工作模式（0）、通道二（01）
              icounter=read_ad(16); //读数据寄存器
			 }
		   break;         
	      
        default:
		  
		   break;
		  
}	
  //ENABLETIM2;  
}

void ad_tim2_init(u16 Arr,u16 Psc)
{
   RCC->APB1ENR|=1<<0;//enable tim2 clock
   TIM2->ARR=Arr;
   TIM2->PSC=Psc;

   TIM2->DIER|=1<<0;   //enable interrupt
   TIM2->DIER|=1<<6;   //awalys

   TIM2->CR1|=0x01;	   //enable tim2
   TIM2_NVIC_Configration();
}
void tim3_init(u16 Arr,u16 Psc)
{
   RCC->APB1ENR|=1<<1;//enable tim3 clock
   TIM3->ARR=Arr;
   TIM3->PSC=Psc;

   //TIM2->DIER|=1<<0;   //enable interrupt
   //TIM2->DIER|=1<<6;   //awalys

   TIM3->CR1|=0x01;	   //enable tim3
   //TIM2_NVIC_Configration();
}

static void TIM2_NVIC_Configration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{
  if(TIM2->SR&0x0001)
  {
	 timeupdataflag=1;
	 freqbuf=freq;
	 freq=0;
	 trytime++;
  }	
 TIM2->SR&=~(1<<0);
}
















