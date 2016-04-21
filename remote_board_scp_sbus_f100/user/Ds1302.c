#include "include.h"

u8 Timedat[6];

void Ds1302_IO_Configration(void)
{
    /*GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	*/
	RCC->APB2ENR|=1<<3;
	GPIOB->CRL&=0xf000ffff;
	GPIOB->CRL|=0x03730000;

}


void write_1302byte(u8 dat)//дһ���ֽڵ�����sck������д����
{
 	u8 i=0;
	GPIO_ResetBits(GPIOB,ds1302clk);
 
    Delay_us(2);//��ʱ��Լ2us
 	for(i=0;i<8;i++)
 	    {
			GPIO_ResetBits(GPIOB,ds1302clk);
 	    	//ds1302clk=0;
			if(dat&0x01)
			GPIO_SetBits(GPIOB,ds1302dat);
			else
			GPIO_ResetBits(GPIOB,ds1302dat);
	 		//ds1302dat=(dat&0x01);
	 		Delay_us(2);
			GPIO_SetBits(GPIOB,ds1302clk);
	 		//ds1302clk=1;
	 		dat>>=1;
	 		Delay_us(1);
 		}	
}
u8 Ds1302ReadByte(uint8_t add)//������
{
	u8 i=0,dat1=0x00;
	GPIO_ResetBits(GPIOB,ds1302rst);
	GPIO_ResetBits(GPIOB,ds1302clk);
	//ds1302rst=0;
	//ds1302clk=0;
	Delay_us(3);//��΢��ʱ2us
	GPIO_SetBits(GPIOB,ds1302rst);
	//ds1302rst=1;
	Delay_us(3);//ʱ��Ҫ��Լ3us
	write_1302byte(add);//��д�Ĵ����ĵ�ַ
	for(i=0;i<8;i++)
	   {
	    GPIO_SetBits(GPIOB,ds1302clk);
		//ds1302clk=1;
		dat1>>=1;
		GPIO_ResetBits(GPIOB,ds1302clk);
		//ds1302clk=0;//����ʱ���ߣ��Ա������ݵĶ���
		if(GPIO_ReadInputDataBit(GPIOB,ds1302dat)==1)//�����ߴ�ʱΪ�ߵ�ƽ
		{dat1=dat1|0x80;}
	  }
	  Delay_us(1);
	  GPIO_ResetBits(GPIOB,ds1302rst);
	  //ds1302rst=0;
	  return dat1;
}
void Ds1302WriteByte(u8 add,u8 dat)//��ָ���Ĵ���д��һ���ֽڵ�����
{
	GPIO_ResetBits(GPIOB,ds1302rst);
	GPIO_ResetBits(GPIOB,ds1302clk);
	//ds1302rst=0;
	//ds1302clk=0;
	Delay_us(1);//��΢��ʱ
	GPIO_SetBits(GPIOB,ds1302rst);
	//ds1302rst=1;
	Delay_us(2);//ʱ���Լ2us
	write_1302byte(add);
	write_1302byte(dat);
	GPIO_ResetBits(GPIOB,ds1302rst);
	GPIO_ResetBits(GPIOB,ds1302clk);
	//ds1302clk=0;
	//ds1302rst=0;
	Delay_us(1);

}

/***********************************************************************
Ds1302:ʱ�����ú���
��ڣ�ʱ���֣���
*************************************************************************/
void Ds1302ConfigTime(u8 year,u8 month,u8 data,u8 hour,u8 min,u8 sec)
{
  
 Ds1302WriteByte(0x8e,0x00);//ȥд������0X00
 year=(year/10)*16+year%10;
 month=(month/10)*16+month%10; 
 data=(data/10)*16+data%10;
 hour=(hour/10)*16+hour%10;
 min=(min/10)*16+min%10;
 sec=(sec/10)*16+sec%10;
 Ds1302WriteByte(0x8c,year);
 Ds1302WriteByte(0x88,month);
 Ds1302WriteByte(0x86,data);
 Ds1302WriteByte(0x84,hour);
 Ds1302WriteByte(0x82,min);
 Ds1302WriteByte(0x80,sec);
 Ds1302WriteByte(0x8e,0x80);//��д������0X80
}
void Ds1302ReadTime(time_s *tp)
{
  u8 year,month,data,hour,min,sec;
  year=Ds1302ReadByte(0x8d);//��
  month=Ds1302ReadByte(0x89);//��
  data=Ds1302ReadByte(0x87);//��
  hour=Ds1302ReadByte(0x85);//ʱ
  min=Ds1302ReadByte(0x83);//��
  sec=Ds1302ReadByte(0x81);//��
  tp->year[0]='2';
  tp->year[1]='0';
  tp->year[2]=year/16+'0';
  tp->year[3]=year%16+'0';
  tp->month[0]=month/16+'0';
  tp->month[1]=month%16+'0';
  tp->data[0]=data/16+'0';
  tp->data[1]=data%16+'0';
  tp->hour[0]=hour/16+'0';
  tp->hour[1]=hour%16+'0';
  tp->min[0]=min/16+'0';
  tp->min[1]=min%16+'0';
  tp->sec[0]=sec/16;
  tp->sec[1]=sec%16;
}







