#include <stm32f10x.h>
#include "VS10XX.h"	
#include "delay.h" 	 
#include "spi.h"


 	   	 
void VS_Write_Reg(unsigned char addr,unsigned int dat)
{
 VS_DREQ_SET;
 while(!VS_DREQ);

 VS_XCS_CLR;
 SPIx_ReadWriteByte(VS_WRITE_COMMAND);   //д����
 SPIx_ReadWriteByte(addr);	             //д���ַ
 SPIx_ReadWriteByte(dat>>8);             //д����ֽ�
 SPIx_ReadWriteByte(dat);				 //д����ֽ�
 VS_XCS_SET;
}
unsigned int VS_Read_Reg(unsigned char addr)
{
 unsigned int temp=0;
 VS_DREQ_SET;
 while(!VS_DREQ);
 VS_XCS_CLR;
 SPIx_ReadWriteByte(VS_READ_COMMAND);     //������
 SPIx_ReadWriteByte(addr);
 temp=SPIx_ReadWriteByte(0xff);			  //�����߰�λ
 temp<<=8;								  
 temp|=SPIx_ReadWriteByte(0xff);		  //�����Ͱ�λ
 VS_XCS_SET;
 return temp;
}

void VS_Reset(void)
{
 VS_XRESET_SET;
 Delay_ms(1);
 VS_XRESET_CLR;
 Delay_ms(1);
 VS_XRESET_SET;
 Delay_ms(1);

 VS_Write_Reg(VS_MODE,0x0804);
 VS_Write_Reg(VS_MODE,0x0800);
 VS_Write_Reg(5,0xbb81);
 VS_Write_Reg(VS_CLOCKF,0x9800);
 VS_Write_Reg(VS_VOL,0x4040);

 VS_XDCS_CLR;
 SPIx_ReadWriteByte(0);
 SPIx_ReadWriteByte(0);
 SPIx_ReadWriteByte(0);
 SPIx_ReadWriteByte(0);
 VS_XDCS_SET;
}

void VS_Send_Dat(unsigned char Dat)
{
// unsigned char i;
// VS_DREQ_SET;
 while(!VS_DREQ);
 SPIx_ReadWriteByte(Dat);
}

void VS_Flash_Buffer(void)
{
 unsigned int i=0;
 VS_XDCS_CLR;
 for(i=0;i<2048;i++)
 {
   VS_Send_Dat(0);
 }
 VS_XDCS_SET;
}

void VS_sin_test(unsigned char x)
{
  VS_Write_Reg(0x00,0x0820);//��������
  VS_DREQ_SET;
  while(!VS_DREQ);
  VS_XDCS_CLR;
  SPIx_ReadWriteByte(0x53);	//�������Ҳ���
  SPIx_ReadWriteByte(0xef);
  SPIx_ReadWriteByte(0x6e);
  SPIx_ReadWriteByte(x);
  SPIx_ReadWriteByte(0);
  SPIx_ReadWriteByte(0);
  SPIx_ReadWriteByte(0);
  SPIx_ReadWriteByte(0);
  Delay_ms(200);
  SPIx_ReadWriteByte(0x45);	//�˳���ͳ����
  SPIx_ReadWriteByte(0x78);
  SPIx_ReadWriteByte(0x69);
  SPIx_ReadWriteByte(0x74);
  SPIx_ReadWriteByte(0);
  SPIx_ReadWriteByte(0);
  SPIx_ReadWriteByte(0);
  SPIx_ReadWriteByte(0);
  VS_XDCS_SET;
}






									 
	   	   


