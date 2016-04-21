#ifndef _ILI9325_GUI_H_
#define _ILI9325_GUI_H_

#include "stm32f10x.h"	
#include "ili9325.h"
#include "delay.h"

extern u16  LCD_GetPoint(u16 x,u16 y);
extern void LCD_SetPoint(u16 x,u16 y);

extern void Int_to_Str(int dd,unsigned char *str);
extern void LCD_Show_Char(unsigned int x,unsigned int y,unsigned char value);
extern void LCD_Show_Str(unsigned int x,unsigned int y,unsigned char str[]);
extern void LCD_Show_Int(unsigned int x,unsigned int y, int Value);

extern u16  LCD_BGR_TO_RGB(u16 c);
extern void LCD_DrawLine(u8 x1, u16 y1, u8 x2, u16 y2);
extern void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Height, u16 Width);
extern void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius);
extern void LCD_DrawMonoPict(uc32 *Pict);
extern void LCD_WriteBMP(u32 BmpAddress);

#endif


