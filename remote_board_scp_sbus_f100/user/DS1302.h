#ifndef _DS1302_H__
#define _DS1302_H__

#define CLK_SET GPIOB->ODR|=1<<6
#define CLK_CLR GPIOB->ODR&=~(1<<6)

#define IO_SET   GPIOB->ODR|=1<<5
#define IO_CLR   GPIOB->ODR&=~(1<<5)

#define RST_SET  GPIOB->ODR|=1<<4
#define RST_CLR  GPIOB->ODR&=~(1<<4)

#define IO_INPUT  GPIOB->CRL&=0xff0fffff; GPIOB->CRL|=0x00800000

#define IO_OUTPUT GPIOB->CRL&=0xff0fffff; GPIOB->CRL|=0x00300000

#define IO_STA   !!(GPIOB->IDR&(1<<5))

#define ds1302clk GPIO_Pin_6
#define ds1302dat GPIO_Pin_5
#define ds1302rst GPIO_Pin_4 

typedef struct time_ck{
u8 year[4];
u8 month[2];
u8 data[2];
u8 hour[2];
u8 min[2];
u8 sec[2];
}time_s;







void Ds1302_IO_Configration(void);
void Ds1302WriteByte(unsigned char addr,unsigned char dat);
unsigned char Ds1302ReadByte(unsigned char addr);
void Ds1302ReadTime(time_s *tp);
void Ds1302ConfigTime(u8 year,u8 month,u8 data,u8 hour,u8 min,u8 sec);
extern unsigned char Timedat[6];
#endif

