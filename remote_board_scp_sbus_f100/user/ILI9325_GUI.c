#include "ILI9325_GUI.h"
#include "stm32f10x.h"
#include "ILI9325.h"	
#include "delay.h"
#include "Font.h" 
#include "ff.h"
#include "diskio.h"
extern vu16 TextColor;
extern vu16 BackColor;
extern vu16 DeviceCode;
/*---------------------------------------------------------------*/
void LCD_Show_HZ(unsigned int x,unsigned int y,unsigned char HZtab[])
{

 unsigned int i=0,j=0,k=0;


 LCD_SetWindow(x,y,x+15,y+15); 
 for(j=0;j<32;j+=2)
 {
   for(i=0;i<8;i++)
   {
    
	 if((HZtab[j]<<i)&0x80) LCD->LCD_RAM=Black;
	 else LCD->LCD_RAM=White;
   }
   for(i=0;i<8;i++)
   {
    
	 if((HZtab[j+1]<<i)&0x80) LCD->LCD_RAM=Black;
	 else LCD->LCD_RAM=White;
   }
 }    
}


/*******************************************************************************
* Function Name  : Int_to_Str
* Description    : 将整形数转换为字符串
* Input          : int x,int y,char Str[]
* Output         : None
* Return         : None
*******************************************************************************/
void Int_to_Str(int dd,unsigned char *str)
{
	str[0]=dd/10000+48;
	str[1]=(dd/1000)-((dd/10000)*10)+48;
	str[2]=(dd/100)-((dd/1000)*10)+48;
	str[3]=(dd/10)-((dd/100)*10)+48;
	str[4]=dd-((dd/10)*10)+48;
	str[5]=0;
}
/*******************************************************************************
* Function Name  : LCD_Show_Char
* Description    : 在指定位置显示一个字符(8*12大小)
* Input          : int x,int y,char Str[]
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Show_Char(unsigned int x,unsigned int y,unsigned char value)	
{  
	unsigned char i,j;
	unsigned char *temp=Font;

	temp+=(value-32)*12;

    LCD_SetWindow(x,y,x+11,y+7);       //设置区域 
	LCD_WriteRAM_Prepare();
	for(j=0;j<12;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
            if(((*temp)&(1<<(7-i)))!=0)
			{ 
				LCD_WriteRAM(TextColor);
			} 
		 	else
			{
		 		LCD_WriteRAM(BackColor);
			}   
		}
		temp++;
	 }
}
/*******************************************************************************
* Function Name  : LCD_Show_Str
* Description    : 在指定位置显示一个字符串(8*12大小)
* Input          : int x,int y,char Str[]
* Output         : None
* Return         : None
*******************************************************************************/

void LCD_Show_Str(unsigned int x,unsigned int y,unsigned char *str)	  
{  
    unsigned int x1,y1;
	x1=x;
	y1=y;
	while(*str!='\0')
	{	
		LCD_Show_Char(x1,y1,*str); 
		y1+=8;
		str++;
	}	
}
/*******************************************************************************
* Function Name  : LCD_Show_Int
* Description    : 在指定位置显示一个Int(8*12大小)
* Input          : int x,int y,char Str[]
* Output         : None
* Return         : None
*******************************************************************************/

void LCD_Show_Int(unsigned int x,unsigned int y, int Value)	  
{     
	unsigned char str[5];
	Int_to_Str(Value,str);
	//LCD_Show_Str(x,y,str);
}

/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Height, u16 Width)
{
  LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
  LCD_DrawLine((Xpos + Height), Ypos, Width, Horizontal);
  
  LCD_DrawLine(Xpos, Ypos, Height, Vertical);
  LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, Vertical);
}

/*******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : Displays a circle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius)
{
  s32  D;/* Decision Variable */ 
  u32  CurX;/* Current X Value */
  u32  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos + CurX, Ypos - CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos - CurX, Ypos + CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos - CurX, Ypos - CurY);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos + CurY, Ypos - CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos - CurY, Ypos + CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    LCD_SetCursor(Xpos - CurY, Ypos - CurX);
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    LCD_WriteRAM(TextColor);

    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

/*******************************************************************************
* Function Name  : LCD_DrawMonoPict
* Description    : Displays a monocolor picture.
* Input          : - Pict: pointer to the picture array.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawMonoPict(uc32 *Pict)
{
  u32 index = 0, i = 0;

  LCD_SetCursor(0, 319); 

  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
  for(index = 0; index < 2400; index++)
  {
    for(i = 0; i < 32; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        LCD_WriteRAM(BackColor);
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
  }
}
/****************************************************************************
* 名    称：u16 LCD_BGR_TO_RGB(u16 c)
* 功    能：BBBBBGGGGGGRRRRR 改为 RRRRRGGGGGGBBBBB格式
* 入口参数：BRG 颜色值
* 出口参数：RGB 颜色值
* 说    明：内部函数调用
* 调用方法：
****************************************************************************/
u16 LCD_BGR_TO_RGB(u16 c)
{
  u16  r, g, b, rgb;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);

  return( rgb );
}
/****************************************************************************
* 名    称：u16 LCD_GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=LCD_GetPoint(10,10);
****************************************************************************/
u16 LCD_GetPoint(u16 x,u16 y)
{
  LCD_SetCursor(x,y);
  return (LCD_BGR_TO_RGB(LCD_ReadRAM()));
}
/****************************************************************************
* 名    称：void LCD_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：LCD_SetPoint(10,10,0x0fe0);
****************************************************************************/
void LCD_SetPoint(u16 x,u16 y)
{
  if ( (x>240)||(y>320) ) return;
  LCD_SetCursor(x,y);
  LCD_WriteRAM_Prepare();
  LCD_WriteRAM(TextColor);
}


/*******************************************************************************
* Function Name  : LCD_WriteBMP
* Description    : Displays a bitmap picture loaded in the internal Flash.
* Input          : - BmpAddress: Bmp picture address in the internal Flash.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteBMP(u32 BmpAddress)
{
  u32 index = 0, size = 0;

  /* Read bitmap size */
  size = *(vu16 *) (BmpAddress + 2);
  size |= (*(vu16 *) (BmpAddress + 4)) << 16;

  /* Get bitmap data address offset */
  index = *(vu16 *) (BmpAddress + 10);
  index |= (*(vu16 *) (BmpAddress + 12)) << 16;

  size = (size - index)/2;

  BmpAddress += index;

  /* Set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(0x03, 0x1008);
 
  LCD_WriteRAM_Prepare();
 
  for(index = 0; index < size; index++)
  {
    LCD_WriteRAM(*(vu16 *)BmpAddress);
    BmpAddress += 2;
  }
 
  /* Set GRAM write direction and BGR = 1 */
  /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
  /* AM = 1 (address is updated in vertical writing direction) */
  LCD_WriteReg(0x03, 0x1018);
}
//*******************************************
 int Abs(int Data)
{
 if(Data<0)
 Data=Data-2*Data;
 return Data;
}
//********************************************
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u8 x1, u16 y1, u8 x2, u16 y2)
{
    u16 x, y, t;
	if((x1==x2)&&(y1==y2))LCD_SetPoint(x1, y1);
	else if(Abs(y2-y1)>Abs(x2-x1))//斜率大于1 
	{
		if(y1>y2) 
		{
			t=y1;
			y1=y2;
			y2=t; 
			t=x1;
			x1=x2;
			x2=t; 
		}
		for(y=y1;y<y2;y++)//以y轴为基准 
		{
			x=(u32)(y-y1)*(x2-x1)/(y2-y1)+x1;		 
			LCD_SetPoint(x, y);  
		}
	}
	else     //斜率小于等于1 
	{
		if(x1>x2)
		{
			t=y1;
			y1=y2;
			y2=t;
			t=x1;
			x1=x2;
			x2=t;
		}   
		for(x=x1;x<=x2;x++)//以x轴为基准 
		{
			y =(u32)(x-x1)*(y2-y1)/(x2-x1)+y1;
			LCD_SetPoint(x,y); 
		}
	} 
} 

