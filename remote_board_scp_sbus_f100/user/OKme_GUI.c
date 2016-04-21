/*********************************************
TFT������ʾ������ 
˵�������㣬���ߣ���Բ����ֱ�ߣ�������  \
���ߣ�NXP 
*********************************************/
#include "stm32f10x.h"
#include "16x8.h"
#include "ili9325.h"

/********************************************/
#define uchar unsigned char
#define uint unsigned int
/*********************************************
����
��ڲ����� (x��y)�ǵ�����꣬color �ǵ����ɫ��
˵������ָ������ɫ��ָ��������λ���ϻ���һ���㡣
*********************************************/
void OKme_Point(unsigned int x,unsigned int y,unsigned int color)
{
 LCD_SetWindow(x,y,x,y);
 LCD->LCD_RAM=color;
}

void OKme_Char(uchar x, uint y,uchar c, uint color,uint b_color)
{  
 unsigned int i,j,Cinfo;
 LCD_SetWindow(x,y,x+8,y+16);
 Cinfo=(c-32)*16;
 for(j=Cinfo;j<Cinfo+16;j++)
 {
   	for(i=0;i<9;i++)
	{
	   if((OKme_font16x8[j]<<i)&0x80)
	   {
	     LCD->LCD_RAM=color;
	   }
	   else
	   {
	     LCD->LCD_RAM=b_color;
	   }
	}
 
 }
 

}
/*********************************************
��ʾӢ���ַ���
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����꣬*s��Ӣ���ַ���ָ�룬
          color:��ɫ,b_color:������ɫ��
*********************************************/
void OKme_String(uint x, uint y,char  *s, uint color,uint b_color)
{  
	for(;*s!='\0';s++)
	{
		OKme_Char(x, y,*s, color,b_color);
		x=x+8;
    }
}
