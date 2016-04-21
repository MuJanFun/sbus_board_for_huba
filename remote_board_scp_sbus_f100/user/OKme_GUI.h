#ifndef __OKme_GUI_H__
#define __OKme_GUI_H__
/********************************/
#define uchar unsigned char
#define uint unsigned int
/*********************************************/

void OKme_Point(unsigned int x,unsigned int y,unsigned int color);
void OKme_Char(uchar x, uint y,uchar c, uint color,uint b_color);
void OKme_String(uint x, uint y,char  *s, uint color,uint b_color);

#endif 

