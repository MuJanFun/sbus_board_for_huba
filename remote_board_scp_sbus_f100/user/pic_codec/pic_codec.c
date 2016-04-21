#include "stm32f10x.h"
#include "ff.h"
#include "ili9325.H"
#include "pic_codec.h"
//#include "tjpgd.h"
u16 width,height;

/*------------------------------*/
/* User defined input funciton  */
/*------------------------------*/

UINT in_func (JDEC* jd, BYTE* buff, UINT nbyte)
{
UINT br;
FIL *dev = (FIL*)jd->device;   /* Device identifier for the session (5th argument of jd_prepare function) */
if (buff) 
	{
	/* Read bytes from input stream */
	f_read(dev,buff,nbyte,&br);
	return br;
	} 
else 
	{
	/* Remove bytes from input stream */
	if(f_lseek(dev, dev->fptr + nbyte) == FR_OK)
		{
		return nbyte;
		}
	else
		{
		
		return 0;
		}
//	return (f_lseek(dev, f_tell(dev) + nbyte) == FR_OK) ? nbyte : 0;
	}
}


/*------------------------------*/
/* User defined output funciton */
/*------------------------------*/

UINT out_func (JDEC* jd, void* bitmap, JRECT* rect)
{
//		disp_blt(rect->left, rect->right, rect->top, rect->bottom, (u16*)bitmap);
u16* d;
u16 i;
d=bitmap;
//LCD_Window(rect->left, rect->right, rect->top, rect->bottom);
LCD_SetWindow((320-width)/2+rect->left,(240-height)/2+rect->top,(320-width)/2+rect->right,(240-height)/2+rect->bottom);
for(i=0;i<(rect->right-rect->left+1)*(rect->bottom-rect->top+1);i++)
	{
     LCD->LCD_RAM=*d++;
	}
return 1;    /* Continue to decompress */
}



void load_jpg(FIL*fp,void*work,u16 sz_work)
{

JDEC jd;
u8 scale=0;

LCD_Clear(Black);
jd_prepare(&jd, in_func,work,sz_work, fp);
width=jd.width;
height=jd.height;
while(width>320||height>240)
	{
	width/=2;
	height/=2;
	scale+=1;
	}
jd_decomp(&jd, out_func, scale);
}

void load_bmp(FIL*fp,void*work,u16 sz_work)
{
u16 data,width,height;
u16 i;
UINT br;
u8*buffer;
u16 sz_read=sz_work;
u8 pixel_skip=0;
struct bmpfile
{
WORD flag;//文件标识;BM为位图文件;偏移:0x0000;
DWORD size;//文件大小;偏移:0x0002;
DWORD offset;//位图数据偏移;偏移:0x000A;
}BMP_FILE;//位图文件头

struct bmpmessage
{
DWORD width;//位图的宽度;偏移:0x0012;
DWORD height;//位图的高度;偏移:0x0016;
WORD BPP;//每个像素点所需要的数据位数;偏移:0x001C;
DWORD compression;//压缩算法;偏移:0x001E;
DWORD sz_data;//位图数据大小
}BMP_HEAD;//位图信息头

buffer=work;

LCD_Clear(Black);
f_lseek(fp, 0);
f_read(fp,buffer,512,&br);


/*位图文件头*/
BMP_FILE.flag=*(buffer+1)+(*buffer<<8);
BMP_FILE.size=*(buffer+2)+(*(buffer+3)<<8)+(*(buffer+4)<<16)+(*(buffer+5)<<24);
BMP_FILE.offset=*(buffer+10)+(*(buffer+11)<<8)+(*(buffer+12)<<16)+(*(buffer+13)<<24);
/*位图信息头*/
BMP_HEAD.width=*(buffer+18)+(*(buffer+19)<<8)+(*(buffer+20)<<16)+(*(buffer+21)<<24);
BMP_HEAD.height=*(buffer+22)+(*(buffer+23)<<8)+(*(buffer+24)<<16)+(*(buffer+25)<<24);
BMP_HEAD.sz_data=*(buffer+34)+(*(buffer+35)<<8)+(*(buffer+36)<<16)+(*(buffer+37)<<24);
BMP_HEAD.BPP=*(buffer+28)+(*(buffer+29)<<8);
BMP_HEAD.compression=*(buffer+30)+(*(buffer+31)<<8)+(*(buffer+32)<<16)+(*(buffer+33)<<24);
	
if(BMP_FILE.flag!=0x424D)
	return;
if(BMP_HEAD.compression!=0)
	return;
if(BMP_HEAD.sz_data==0)
	return;

width=BMP_HEAD.width;
height=BMP_HEAD.height;
while(width>320||height>240)
	{
	pixel_skip++;
	width=BMP_HEAD.width/(pixel_skip+1);
	height=BMP_HEAD.height/(pixel_skip+1);
	}

sz_read=BMP_HEAD.sz_data/BMP_HEAD.height;
f_lseek(fp, BMP_FILE.offset);
LCD_WriteReg(0x0001,0x0100);//从下到上扫描
LCD_SetWindow((320-width)/2,(240-height)/2,(320+width)/2-1,(240+height)/2);
br=sz_read;
	
switch(BMP_HEAD.BPP)
	{
	case(24):
	while(br==sz_read)
		{
		f_read(fp,buffer,sz_read,&br);
		switch(pixel_skip)
			{
			case(0):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+3*i)>>3)+((*(buffer+3*i+1)>>2)<<5)+(*(buffer+3*i+2)>>3<<11);
				LCD->LCD_RAM=data;
				}
			break;
			case(1):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+6*i)>>3)+((*(buffer+6*i+1)>>2)<<5)+(*(buffer+6*i+2)>>3<<11);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			break;
			case(2):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+9*i)>>3)+((*(buffer+9*i+1)>>2)<<5)+(*(buffer+9*i+2)>>3<<11);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			break;		
			case(3):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+12*i)>>3)+((*(buffer+12*i+1)>>2)<<5)+(*(buffer+12*i+2)>>3<<11);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			break;		
			case(4):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+15*i)>>3)+((*(buffer+15*i+1)>>2)<<5)+(*(buffer+15*i+2)>>3<<11);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			break;				
			}
		}
	break;
	case(16):
	while(br==sz_read)
		{
		f_read(fp,buffer,sz_read,&br);
		switch(pixel_skip)
			{
			case(0):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+2*i+1)*512)+((*(buffer+2*i+1)&0xE0)*2)+(*(buffer+2*i+1)&0x1F);
				LCD->LCD_RAM=data;
				}
			break;
			case(1):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+4*i+1)*512)+((*(buffer+4*i+1)&0xE0)*2)+(*(buffer+4*i+1)&0x1F);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			break;
			case(2):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+6*i+1)*512)+((*(buffer+6*i+1)&0xE0)*2)+(*(buffer+6*i+1)&0x1F);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			break;		
			case(3):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+8*i+1)*512)+((*(buffer+8*i+1)&0xE0)*2)+(*(buffer+8*i+1)&0x1F);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			break;		
			case(4):
			for(i=0;i<width;i++)
				{
				data=(*(buffer+10*i+1)*512)+((*(buffer+10*i+1)&0xE0)*2)+(*(buffer+10*i+1)&0x1F);
				LCD->LCD_RAM=data;
				}
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			f_read(fp,buffer,sz_read,&br);
			break;				
			}
		}
	break;
	}
//LCD_WriteReg(0x0001,0x0000);
}










