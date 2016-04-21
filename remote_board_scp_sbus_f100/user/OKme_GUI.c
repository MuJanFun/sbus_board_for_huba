/*********************************************
TFT基本显示函数集 
说明：画点，画线，画圆，画直线，画虚线  \
作者：NXP 
*********************************************/
#include "stm32f10x.h"
#include "16x8.h"
#include "ili9325.h"

/********************************************/
#define uchar unsigned char
#define uint unsigned int
/*********************************************
画点
入口参数： (x，y)是点的坐标，color 是点的颜色。
说明：用指定的颜色在指定的坐标位置上画出一个点。
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
显示英文字符串
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
*********************************************/
void OKme_String(uint x, uint y,char  *s, uint color,uint b_color)
{  
	for(;*s!='\0';s++)
	{
		OKme_Char(x, y,*s, color,b_color);
		x=x+8;
    }
}
