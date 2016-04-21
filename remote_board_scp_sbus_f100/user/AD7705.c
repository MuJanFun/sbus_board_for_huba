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

  //PC0(sclk),PC1(reset),PC2(DIN) OutPut��PC3(DOUT)��InPut
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
	  case 1:  //setp1  Ad��λ
	    
		 RESET_CLR;  //reset�ź���Ч
         Delay_ms(10);  //��ʱ10ms
         RESET_SET;  //reset�ź���Ч
         break;
		
	  case 2:  //setp2  ADͨ��һ��ʼ����1������У׼
	    
		 write_ad(0x20);//дͨ�żĴ�����00100000�����루0����ʱ�ӼĴ�����010����д��0������������ģʽ��0����ͨ��һ��00��
         write_ad(0x04);//дʱ�ӼĴ�����00000010�����루000������ʱ�ӹرգ�0����ʱ�Ӳ���Ƶ��0����2.4576��1����50HZ�����00��
         write_ad(0x10);//дͨ�żĴ�����00010000�����루0�������üĴ�����001����д��0������������ģʽ��0����ͨ��һ��00��
         write_ad(0x40);//д���üĴ�����01000100����У׼��01����1�����棨000����˫���ԣ�0�����ǻ��壨0��������״̬��0��

		 write_ad(0x18);//дͨ�żĴ�����00010000�����루0�������üĴ�����001��������1������������ģʽ��0����ͨ��һ��00��
		 //while(DRDY_STA);
		 //adset=read_ad(8);



		 Delay_ms(40); //��ʱ40ms
	     break;
		
	  case 3:  //�ղ���  ��ʱ
        
		  //Send_Dat();
		 //twohundredusdelay(200);  //��ʱ40ms
		 break;
		
	  case 4:  //�ղ���  ��ʱ
        
		Delay_ms(60);//��ʱ40ms 
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
		
	  case 5:  //step3  ADͨ��һ1��������������
	    
	     write_ad(0x10);//дͨ�żĴ�����00010000�����루0�������üĴ�����001����д��0������������ģʽ��0����ͨ��һ��00��
         write_ad(0x00);//д���üĴ�����00000100������������00����1�����棨000����˫���ԣ�0�����ǻ��壨0��������״̬��0��
         break;
 	    
      case 6:  //step4����ȡADͨ��һ��ֵ���޸����沢У׼n������
	    
	
	     while(DRDY_STA);
		 if(DRDY_STA==0)///d/r/a/y/YΪ�͵�ƽ���ݿ���
           {
            write_ad(0x38);//дͨ�żĴ�����00111000�����루0�������ݼĴ�����011��������1������������ģʽ��0����ͨ��һ��00��
            vcounter=read_ad(16); //�����ݼĴ���  
           }           
          Delay_ms(40);  //��ʱ40ms
		  break;   
		
	  case 7://Step9��ADͨ������ʼ����1������У׼
        
	     write_ad(0x11);//дͨ�żĴ�����00010001�����루0�������üĴ�����001����д��0������������ģʽ��0����ͨ������01��
         write_ad(0x44);//д���üĴ�����01000100����У׼��01����1�����棨000���������ԣ�1�����ǻ��壨0��������״̬��0��
         Delay_ms(40);  //��ʱ40ms
         break;
	     
	  case 8:    //�ղ���  ��ʱ
          
	 	   Delay_ms(60); //��ʱ40ms
		   bats=(float)icounter/65536*0.99*9.25;
		   if(bats<=7.4) NoUsartDMAEnable(&fsac,battery,0); 
		   if((bats>7.4)&&(bats<=7.7)) NoUsartDMAEnable(&fsac,battery,1); 
		   if((bats>7.7)&&(bats<=7.8)) NoUsartDMAEnable(&fsac,battery,2); 
		   if((bats>7.8)&&(bats<=7.9)) NoUsartDMAEnable(&fsac,battery,3);  
		   if(bats>7.9) NoUsartDMAEnable(&fsac,battery,4); 
	  	   break;
	        
        case 9:  //�ղ���  ��ʱ
          
		    Delay_ms(40);  //��ʱ40ms
			printf((const char *)ReadRTC);
		   break;
	        
	    case 10://Step10��ADͨ����1��������������
          
		   write_ad(0x11);//дͨ�żĴ�����00010001�����루0�������üĴ�����001����д��0������������ģʽ��0����ͨ������01��
           write_ad(0x04);//д���üĴ�����00000100������������00����1�����棨000���������ԣ�1�����ǻ��壨0��������״̬��0��
           break;
 	      
        case 11://Step11����ȡͨ��������ֵ
           
		   
	       while(DRDY_STA); 
	        if(DRDY_STA==0)
	         {
		      write_ad(0x39);//дͨ�żĴ�����00111001�����루0�������ݼĴ�����011��������1������������ģʽ��0����ͨ������01��
              icounter=read_ad(16); //�����ݼĴ���
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
















