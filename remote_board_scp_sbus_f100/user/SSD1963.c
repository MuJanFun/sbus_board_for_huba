/*******************************************

				  7�� AT070TN92��ʾ��������







**********************************************/


#include "fsmc_sram.h"
#include "stdlib.h"
#include "font.h"
#include "stm32f10x_tim.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR

//extern struct tm time_now;
unsigned long color1=0;
/*
//TFTLCD������ɫ�Ķ���		
#define RED	  0XF800
#define GREEN 0X07E0
#define BLUE  0X001F  
#define BRED  0XF81F
#define GRED  0XFFE0
#define GBLUE 0X07FF
#define 0XFFFF 0XFFFF //��ɫ
#define BLACK 0X0000 //��ɫ
#define BROWN 0XBC40 //��ɫ
#define BRRED 0XFC07 //�غ�ɫ
#define GRAY  0X8430 //��ɫ
#define LGRAY 0XC618 //ǳ��ɫ
 */

//TFTLCD������ɫ�Ķ���		
#define RED	  0XF800
#define GREEN 0X07E0
#define BLUE  0X001F  
#define BRED  0XF81F
#define GRED  0XFFE0
#define GBLUE 0X07FF

#define WHITE 0Xffff //��ɫ
//#define WHITE  0Xffe0//��ɫ

#define BLACK 0X0000 //��ɫ
#define BROWN 0XBC40 //��ɫ
#define BRRED 0XFC07 //�غ�ɫ
#define GRAY  0X8430 //��ɫ
#define LGRAY 0XC618 //ǳ��ɫ
 
#define FSIZE 16


//=================================================================================

//�ߴ�������ʾ����

//=================================================================================

unsigned int  HDP=799; //Horizontal Display Period
unsigned int  HT=1000; //Horizontal Total
unsigned int  HPS=51;  //LLINE Pulse Start Position
unsigned int  LPS=3;   //	Horizontal Display Period Start Position
unsigned char HPW=8;   //	LLINE Pulse Width


unsigned int  VDP=479;	//Vertical Display Period
unsigned int  VT=530;	//Vertical Total
unsigned int  VPS=24;	//	LFRAME Pulse Start Position
unsigned int  FPS=23;	//Vertical Display Period Start Positio
unsigned char   VPW=3;	// LFRAME Pulse Width




const unsigned short title[]={0x44DF,0x141f,0x141F,0x71f,0x31E,0x2fc,0x2DC,0x2cc,0x2BC,0x2ac,0x29C,0x29c,0x2BC,0x2BC,0x2BC,0x2BC,0x2BD,0x2BD,0x2DE,0x2DE,0x2de,0x31F,0x31f,0x31f,0x35F,0x35F,0x35F,0x33F,0x33f,0x33f,0x2DE,0x2de,0x219};
const unsigned short bt0[]={0xFED2,0xFFB6,0xFF95,0xFF95,0xFF74,0xFF53,0xFF73,0xFF52,0xFF52,0xFF51,0xFF30,0xFF30,0xFF0F,0xFEED,0xFF0F,0xFEED,0xFECA,0xFECC,0xFECC,0xFECB,0xFEA9,0xFE88,0xFEA9,0xFE86,0xFE88,0xFE66,0xFE86,0xFEA7,0xFD41,};
const unsigned short zsq1[]={0xCF7E,0xA6BC,0xB71D,0xA6DC,0xA6FD,0xAF3D,0xA6DC,0xC79F,0xC77F,0x9EBB,0x865A,0x8EDD,0xA6FE,0xB6DC,0xB6FC,0xCF5D,0xF7DF,};

void lcd_pic2(unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned short * src);
void lcd_text16(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, char *s);
void lcd_text24(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, char *s);
void Light_PWM(void);






//unsigned int  POINT_COLOR=RED;//Ĭ�Ϻ�ɫ    
//unsigned int  BACK_COLOR=0XFFFF;//������ɫ.Ĭ��Ϊ��ɫ

//void MUC_Init();
void LCD_Init(void);
void LCD_WR_REG(unsigned int index);
void LCD_WR_CMD(unsigned int index,unsigned int val);

void LCD_WR_Data(unsigned int val);
void LCD_WR_Data_8(unsigned int val);
void LCD_test(void);
void LCD_clear(unsigned int p);
void ini(void);

void lcd_wr_zf(unsigned int a, unsigned int b, unsigned int a1,unsigned int b1, unsigned int d,unsigned int e, unsigned char g, unsigned char *f); 
void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e) ;
unsigned char *num_pub(unsigned int a);

void TFT_Disp_sys_ico(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned char picturenumber);
void TFT_CLEAR(unsigned int color);//TFT��������		    
void TFT_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color);//��ָ���������ָ����ɫ
void TFT_DrawPoint(unsigned int x,unsigned int y,unsigned int fontcolor);
//void TFT_DrawPoint(unsigned short x,unsigned short y,unsigned short fc);

void TFT_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void drow_touch_point(unsigned int x,unsigned int y);
void TFT_ShowChar(unsigned int x,unsigned int y,unsigned int num,unsigned int size,unsigned int mode);
void TFT_ShowString(unsigned int x,unsigned int y,const unsigned char *p);
void drawbigpoint(unsigned int x,unsigned int y);
void draw_circle(unsigned int x0,unsigned int y0,unsigned int r);
void Draw_Sys_ICO(void);
void TFT_ShowNum(unsigned int x,unsigned int y,unsigned int num,unsigned int size,unsigned int mode);
void TFT_Show4Num(unsigned int x,unsigned int y,unsigned int num,unsigned int size,unsigned int mode);
void TFT_ShowBigChar(unsigned int x,unsigned int y,unsigned int num);

void Select_Menu(unsigned char M_Type,unsigned char Cnt,unsigned char En);
void show_font(unsigned int x,unsigned int y,unsigned char position,unsigned char mode);
void delay_time(unsigned int i);

extern void sd_showpic(unsigned short x,unsigned short y,char * fname);


//������ɫ
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR;//������ɫ.Ĭ��Ϊ��ɫ




unsigned int LCD_RD_data(void);
extern void lcd_rst(void);
extern void Delay(__IO uint32_t nCount);


//д�Ĵ�����ַ����
void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;

}



//д�Ĵ������ݺ���
//���룺dbw ����λ����1Ϊ16λ��0Ϊ8λ��
void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

unsigned int LCD_RD_data(void){
	unsigned int a=0;
	//a=(*(__IO uint16_t *) (Bank1_LCD_D)); 	//Dummy
	//a= *(__IO uint16_t *) (Bank1_LCD_D);  	//H
	//a=a<<8;
	a=*(__IO uint16_t *) (Bank1_LCD_D); //L

	return(a);	
}



//д16λ���ݺ���
void    LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

void LCD_WR_Data_8(unsigned int val)
{
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

//��ʼ������
void LCD_Init(void)
{
	lcd_rst();	 


	 LCD_WR_REG(0x00E2);	
	LCD_WR_Data(0x0023);
	// Set PLL with OSC = 10MHz (hardware)
    // Multiplier N = 35, VCO (>250MHz)= OSC*(N+1), VCO = 360MHz	   
	LCD_WR_Data(0x0002);
	// Divider M = 2, PLL = 360/(M+1) = 120MHz
	LCD_WR_Data(0x0004);
	// Validate M and N values

	LCD_WR_REG(0x00E0);  // PLL enable
	LCD_WR_Data(0x0001);
	delay_time(1);
	LCD_WR_REG(0x00E0);
	LCD_WR_Data(0x0003);
	delay_time(5);
	LCD_WR_REG(0x0001);  // software reset
	delay_time(5);
	LCD_WR_REG(0x00E6);	//PLL setting for PCLK, depends on resolution
	//Set LSHIFT freq, i.e. the DCLK with PLL freq 120MHz set previously
	//Typical DCLK for AT070TN92 is 34MHz
	//34MHz = 120MHz*(LCDC_FPR+1)/2^20
	//LCDC_FPR = 300000 (0x0493E0)
	
	
	LCD_WR_Data(0x0004);
	LCD_WR_Data(0x0093);
	LCD_WR_Data(0x00e0);

	//LCD_WR_Data(0x0000);
	//LCD_WR_Data(0x00b4);
	//LCD_WR_Data(0x00e7);


	LCD_WR_REG(0x00B0);	//LCD SPECIFICATION
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_Data(HDP&0X00FF);
    LCD_WR_Data((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_Data(VDP&0X00FF);
    LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_Data((HT>>8)&0X00FF);  //Set HT
	LCD_WR_Data(HT&0X00FF);
	LCD_WR_Data((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(HPS&0X00FF);
	LCD_WR_Data(HPW);			   //Set HPW
	LCD_WR_Data((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(LPS&0X00FF);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_Data((VT>>8)&0X00FF);   //Set VT
	LCD_WR_Data(VT&0X00FF);
	LCD_WR_Data((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_Data(VPS&0X00FF);
	LCD_WR_Data(VPW);			   //Set VPW
	LCD_WR_Data((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_Data(FPS&0X00FF);

	LCD_WR_REG(0x00BA);
	LCD_WR_Data(0x000F);    //GPIO[3:0] out 1

	LCD_WR_REG(0x00B8);
	LCD_WR_Data(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_Data(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x0036); //rotation
	LCD_WR_Data(0x0000);
//	LCD_WR_Data(0x0060);


	LCD_WR_REG(0x00F0); //pixel data interface
	LCD_WR_Data(0x0003);


	delay_time(5);

	//LCD_clear(0xf800);
	TFT_CLEAR(0xf800);
	
	LCD_WR_REG(0x0026); //display on
	LCD_WR_Data(0x0001);

	LCD_WR_REG(0x0029); //display on

	LCD_WR_REG(0x00BE); //set PWM for B/L
	LCD_WR_Data(0x0006);
	//LCD_WR_Data(0x0008);
	LCD_WR_Data(0x0080);
	//LCD_WR_Data(0x00f0);
	
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x00f0);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00d0);//���ö�̬����������� 
	LCD_WR_Data(0x000d);

   	Light_PWM();//���ñ������ȣ����ȴ�С���������		

}

void delay_time(unsigned int i)
{
    unsigned int a;
    unsigned int b;
    for(b=0;b<i;b++)
    for(a=0;a<1000;a++);
}

//��ʾͼƬ x,y:�������
void lcd_pic2(unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned short * src)
{       
	unsigned short i,j;
	 
	LCD_WR_REG(0x002A);	
	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data((x+w-1)>>8);	    
	LCD_WR_Data((x+w-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+h-1)>>8);	    
	LCD_WR_Data((y+h-1)&0x00ff);
	LCD_WR_REG(0x002c);
	
	for(j=0;j<h;j++)
	for(i=0;i<w;i++) 
		LCD_WR_Data(*(src+j));
}



void Draw_Sys_ICO(void)
{

     unsigned char t;
	 unsigned int tx,ty;

	 char * ico[]={"1.bin","2.bin","3.bin","4.bin","5.bin","6.bin","7.bin","8.bin","9.bin","10.bin","11.bin","12.bin",};


	 TFT_CLEAR(WHITE);//����  
//	 TFT_Fill(0,253,479,271,0X81BF);//���ײ���ɫ	
	 
	lcd_pic2(0,0,800,33,title);
	lcd_text24(350,6,0xffff,0xffff,"ϵͳ����");
//	show_font(200,3,7+Cnt*2,0);


	lcd_pic2(0,450,800,29,bt0);




	 tx=20;ty=60;
	for(t=0;t<12;t++)
	{	   
						    
	
		tx=135*(t%6);
		if((t==6)||(t>6))ty=283;
		sd_showpic(tx,ty,ico[t]);
		Select_Menu(0,t,0);//��������

		  
	}

	

 
}




void lcd_text16(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, char *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) {
		if( *s < 0x80 ) {
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	TFT_DrawPoint(x+j,y+i,fc);
					else {
						if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
			}
		else {

			for (k=0;k<hz16_num;k++) {
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1))){ 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	TFT_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	TFT_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			}
			s+=2;x+=16;
			}
		}
}


void lcd_text24(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, char *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) {
		if( *s < 0x80 ) {
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	TFT_DrawPoint(x+j,y+i,fc);
					else {
						if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
			}
		else {

			for (k=0;k<hz24_num;k++) {
			  if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1))){ 
				    for(i=0;i<24;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3]&(0x80>>j))	TFT_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+1]&(0x80>>j))	TFT_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j+8,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+2]&(0x80>>j))	TFT_DrawPoint(x+j+16,y+i,fc);
								else {
									if (fc!=bc) TFT_DrawPoint(x+j+16,y+i,bc);
								}
							}
				    }
				}
			}
			s+=2;x+=24;
			}
		}
}


void Select_Menu(unsigned char M_Type,unsigned char Cnt,unsigned char En)
{
	unsigned int tx;
	unsigned int ty;
	
	char * icotext[]={"ʵʱ״̬","�����趨","��ʷ��¼","��������","������¼","ѹ������","ѹ������"," �ض��� ","�û��趨"," �� �� ","���״̬"," �գӣ� "};
	
		
	ty=180; 
//	LCD_WR_REG(0x0028); //display on
	if(M_Type==0)//���˵�
	{	  
		tx=135*(Cnt%6)+20;//10,90,170			
		
		//if(Cnt>5)ty=205;
		if((Cnt==6)||(Cnt>6))ty=403;	 

		if(En)//ѡ�е�ǰ�Ĳ˵�
		{	  
			POINT_COLOR=WHITE;//��ɫ����
			BACK_COLOR=BLUE;  //��ɫ����      
		}else
		{
			POINT_COLOR=BLACK;//��ɫ����
			BACK_COLOR=WHITE; //��ɫ����   
		}

		lcd_text16(tx,ty,POINT_COLOR,BACK_COLOR,icotext[Cnt]);

	

	}
	//	LCD_WR_REG(0x0029); //display on
	 	  //  POINT_COLOR=WHITE;//��ɫ����
		//	BACK_COLOR=BLUE;  //��ɫ����  
		  	POINT_COLOR=BLACK;//��ɫ����
			BACK_COLOR=WHITE; //��ɫ���� 

}



//��������   
//ȫ����ʾ��ɫ
void TFT_CLEAR(unsigned int color)
{                    
     unsigned int l=800,w;

	LCD_WR_REG(0x002A);	
	LCD_WR_Data(0);	    
	LCD_WR_Data(0);
	LCD_WR_Data(HDP>>8);	    
	LCD_WR_Data(HDP&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(0);	    
	LCD_WR_Data(0);
	LCD_WR_Data(VDP>>8);	    
	LCD_WR_Data(VDP&0x00ff);
	LCD_WR_REG(0x002c);
	
	
	while(l--)
	{
	    for(w=0;w<480;w++)
		{    
          	LCD_WR_Data(color);
		}
	} 
	   
	

}
//��ָ�����������ָ����ɫ
//�����С:
//  (xend-xsta)*(yend-ysta)
void TFT_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color)
{                    
    unsigned long n;

	n=(unsigned long)(yend-ysta+1)*(xend-xsta+1);

 

	LCD_WR_REG(0x002A);	
	LCD_WR_Data(xsta>>8);	    
	LCD_WR_Data(xsta&0x00ff);
	LCD_WR_Data(xend>>8);	    
	LCD_WR_Data(xend&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(ysta>>8);	    
	LCD_WR_Data(ysta&0x00ff);
	LCD_WR_Data(yend>>8);	    
	LCD_WR_Data(yend&0x00ff);

	LCD_WR_REG(0x002c);
  

	while(n--)LCD_WR_Data(color);//��ʾ��ɫ 
	


} 

//��ָ����������ʾϵͳͼ��
//�����С:
//  (xend-xsta)*(yend-ysta)
/*
void TFT_Disp_sys_ico(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned char picturenumber)
{                    
    unsigned long n,disp_pix_num;	
    unsigned int temp;
 // unsigned int l,w;


	disp_pix_num=(unsigned long)(yend-ysta)*(xend-xsta)*2;


	LCD_WR_REG(0x002A);	
	LCD_WR_Data(xsta>>8);	    
	LCD_WR_Data(xsta&0x00ff);
	LCD_WR_Data(xend-1>>8);	    
	LCD_WR_Data(xend-1&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(ysta>>8);	    
	LCD_WR_Data(ysta&0x00ff);
	LCD_WR_Data(yend-1>>8);	    
	LCD_WR_Data(yend-1&0x00ff);
	LCD_WR_REG(0x002c);

	n=0;
	
	while(n<disp_pix_num)
//	while(n<disp_pix_num)
	 { 
	  temp=(uint16_t)( Systerm_ico_XX[n+picturenumber*7080]<<8)+Systerm_ico_XX[n+1+picturenumber*7080];
	  LCD_WR_Data(temp);//��ʾ��ɫ 
	  n=n+2;
	 }	 


}*/
//����
//x:0~239
//y:0~319
//POINT_COLOR:�˵����ɫ
void TFT_DrawPoint(unsigned int x,unsigned int y,unsigned int fontcolor)
{


	LCD_WR_REG(0x002A);	

	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data(HDP>>8);	    
	LCD_WR_Data(HDP&0x00ff);
    LCD_WR_REG(0x002b);	

	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data(VDP>>8);	    
	LCD_WR_Data(VDP&0x00ff);
	LCD_WR_REG(0x002c);	
	
	LCD_WR_Data(fontcolor); 


}  

//��ָ��λ����ʾһ���ַ�
//x:0~234
//y:0~308
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void TFT_ShowChar(unsigned int x,unsigned int y,unsigned int num,unsigned int size,unsigned int mode)
{       
#define MAX_CHAR_POSX 472
#define MAX_CHAR_POSY 264 
    unsigned int temp;
    unsigned int pos,t;      
    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
    //�趨һ���ַ���ռ�Ĵ�С 
    //���ٿռ�

   LCD_WR_REG(0x002A);	
	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data(x+(size/2-1)>>8);	    
	LCD_WR_Data(x+(size/2-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+size-1)>>8);	    
	LCD_WR_Data((y+size-1)&0x00ff);
	LCD_WR_REG(0x002c);

	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//����1206����
			else temp=asc2_1608[num][pos];		 //����1608����
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)
				 // LCD_WR_Data(POINT_COLOR);
		          TFT_DrawPoint(x+t,y+pos,POINT_COLOR);
				else 
				  //LCD_WR_Data(BACK_COLOR); 
				  TFT_DrawPoint(x+t,y+pos,BACK_COLOR);    
		        temp>>=1; 
		    }
		}	
	}else//���ӷ�ʽ
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//����1206����
			else temp=asc2_1608[num][pos];		 //����1608����
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)TFT_DrawPoint(x+t,y+pos,POINT_COLOR);//��һ����     
		        temp>>=1; 
		    }
		}
	}
	

} 
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void TFT_ShowString(unsigned int x,unsigned int y,const unsigned char *p)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;TFT_CLEAR(WHITE);}
        TFT_ShowChar(x,y,*p,16,0);
        x+=8;
        p++;
    }  
}

//��һ�����
//2*2�ĵ�
//��������"��ť"RST

void drawbigpoint(unsigned int x,unsigned int y)
{
	if(x>220&&y<12)
	{
		TFT_CLEAR(WHITE);//���� 
    	TFT_ShowString(220,0,"RST");//��ʾ��������
	}
	else if(x<120&&y<20)
	{
		TFT_DrawPoint(x,y,POINT_COLOR);//���ĵ� 
		TFT_DrawPoint(x+1,y,POINT_COLOR);
		TFT_DrawPoint(x,y+1,POINT_COLOR);
		TFT_DrawPoint(x+1,y+1,POINT_COLOR);	
	}
	else if(y>20){
		TFT_DrawPoint(x,y,POINT_COLOR);//���ĵ� 
		TFT_DrawPoint(x+1,y,POINT_COLOR);
		TFT_DrawPoint(x,y+1,POINT_COLOR);
		TFT_DrawPoint(x+1,y+1,POINT_COLOR);	
	}		  	
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void TFT_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    unsigned int x, y, t;
	if((x1==x2)&&(y1==y2))TFT_DrawPoint(x1, y1,POINT_COLOR);
	else if(abs(y2-y1)>abs(x2-x1))//б�ʴ���1 
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
		for(y=y1;y<y2;y++)//��y��Ϊ��׼ 
		{
			x=(unsigned long)(y-y1)*(x2-x1)/(y2-y1)+x1;
			TFT_DrawPoint(x, y,POINT_COLOR);  
		}
	}
	else     //б��С�ڵ���1 
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
		for(x=x1;x<=x2;x++)//��x��Ϊ��׼ 
		{
			y =(unsigned long)(x-x1)*(y2-y1)/(x2-x1)+y1;
			TFT_DrawPoint(x,y,POINT_COLOR); 
		}
	} 
}

//��һ��������
//����У׼�õ�
void drow_touch_point(unsigned int x,unsigned int y)
{
	TFT_DrawLine(x-12,y,x+13,y);//����
	TFT_DrawLine(x,y-12,x,y+13);//����
	TFT_DrawPoint(x+1,y+1,POINT_COLOR);
	TFT_DrawPoint(x-1,y+1,POINT_COLOR);
	TFT_DrawPoint(x+1,y-1,POINT_COLOR);
	TFT_DrawPoint(x-1,y-1,POINT_COLOR);
	draw_circle(x,y,6);//������Ȧ
}	

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void draw_circle(unsigned int x0,unsigned int y0,unsigned int r)
{
	int a,b;
	int di;
	a=0;
	b=r;
	di=3-2*r;             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		TFT_DrawPoint(x0-b,y0-a,POINT_COLOR);             //3           
		TFT_DrawPoint(x0+b,y0-a,POINT_COLOR);             //0           
		TFT_DrawPoint(x0-a,y0+b,POINT_COLOR);             //1       
		TFT_DrawPoint(x0-b,y0-a,POINT_COLOR);             //7           
		TFT_DrawPoint(x0-a,y0-b,POINT_COLOR);             //2             
		TFT_DrawPoint(x0+b,y0+a,POINT_COLOR);             //4               
		TFT_DrawPoint(x0+a,y0-b,POINT_COLOR);             //5
		TFT_DrawPoint(x0+a,y0+b,POINT_COLOR);             //6 
		TFT_DrawPoint(x0-b,y0+a,POINT_COLOR);             
		a++;
		/***ʹ��Bresenham�㷨��Բ**/     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		TFT_DrawPoint(x0+a,y0+b,POINT_COLOR);
	}
} 



//��ʾ2������
//x,y:�������
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~99);
void TFT_ShowNum(unsigned int x,unsigned int y,unsigned int num,unsigned int size,unsigned int mode)
{         							   
    TFT_ShowChar(x,y,(num/10)%10+'0',size,mode); 
    TFT_ShowChar(x+size/2,y,num%10+'0',size,mode); 
} 
//��ʾ4������
//x,y:�������
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~9999);
void TFT_Show4Num(unsigned int x,unsigned int y,unsigned int num,unsigned int size,unsigned int mode)
{   
	TFT_ShowChar(x,y,(num/1000)+'0',size,mode);
	TFT_ShowChar(x+size/2,y,(num/100)%10+'0',size,mode);      							   
    TFT_ShowChar(x+size,y,(num/10)%10+'0',size,mode); 
    TFT_ShowChar(x+size+size/2,y,num%10+'0',size,mode); 
}

//��ָ��λ����ʾһ�����ַ�
//30*60��С��
//num:0~9
//:/./C�������ַ�
void TFT_ShowBigChar(unsigned int x,unsigned int y,unsigned int num)
{
    unsigned int n,t;
	unsigned int temp;
	unsigned int t1,deadline;

	
	 LCD_WR_REG(0x002A);	
	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data((x+29)>>8);	    
	LCD_WR_Data((x+29)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+59)>>8);	    
	LCD_WR_Data((y+59)&0x00ff);
	LCD_WR_REG(0x002c);


	if(num==':')t1=150;
	else if(num=='.')t1=165;
	else if(num=='C')t1=180;
	else t1=15*num;
	deadline=t1+15;
		   
	for(;t1<deadline;t1++)
	{	 
		for(n=0;n<16;n++)
		{
			temp=BIG_ASCII[t1][n];
			for(t=0;t<8;t++)
			{
				if(temp&0x80) 
				   LCD_WR_Data(POINT_COLOR); 
				  // 	 TFT_DrawPoint(x+t,y+n,POINT_COLOR);
				else 
				    LCD_WR_Data(BACK_COLOR);
					// TFT_DrawPoint(x+t,y+n,BACK_COLOR);
				
				temp<<=1;
				if(((n%4)==3)&&t==5)break;
			}
		}
	} 
	



}

//��ʾһ��ָ����С�ĺ���
//x,y :���ֵ�����
//font:����ASCII��
//mode:0,ȫ���д��.1,��Ч����д��(�ʺ���ͼƬ�ϵ��Ӻ���)
void show_font(unsigned int x,unsigned int y,unsigned char position,unsigned char mode)
{
	unsigned char t1,t2;
	unsigned char temp=0;

 
	LCD_WR_REG(0x0030);
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+FSIZE-1)>>8);	    
	LCD_WR_Data((y+FSIZE-1)&0x00ff);
	
	
	 LCD_WR_REG(0x002A);	
	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data((x+FSIZE-1)>>8);	    
	LCD_WR_Data((x+FSIZE-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+FSIZE-1)>>8);	    
	LCD_WR_Data((y+FSIZE-1)&0x00ff);
	LCD_WR_REG(0x002c);



	if(!mode)//�ǵ���ģʽ
	{
		for(t1=0;t1<FSIZE;t1++)//��FSIZE���ֽ�,ÿ�ζ�����
		{
			temp=HZ_font[t1*2+FSIZE*position*2];
			for(t2=0;t2<8;t2++)
			{
		
			     if(temp&0x80)
				   TFT_DrawPoint(x+t2,y+t1,POINT_COLOR);
				else 
				   TFT_DrawPoint(x+t2,y+t1,BACK_COLOR);    
		        temp<<=1; 
			
			
			}
	 		temp=HZ_font[t1*2+1+FSIZE*position*2];
			for(t2=0;t2<(FSIZE-8);t2++)//�����16*16�������µ��������
			{
			   	 if(temp&0x80)
				   TFT_DrawPoint(x+t2+8,y+t1,POINT_COLOR);
				else 
				   TFT_DrawPoint(x+t2+8,y+t1,BACK_COLOR);    
		        temp<<=1;
			
			}  
		   }
	}else//����ģʽ
	{
		for(t1=0;t1<FSIZE;t1++)//��FSIZE���ֽ�,ÿ�ζ�����
		{
			temp=HZ_font[t1*2+FSIZE*position*2];
			for(t2=0;t2<8;t2++)
			{
				if(temp&0x80)TFT_DrawPoint(x+t2,y+t1,POINT_COLOR);//��һ����	 
				temp<<=1;
			}
		
			temp=HZ_font[t1*2+1+FSIZE*position*2];
			for(t2=0;t2<(FSIZE-8);t2++)//�����16*16�������µ��������
			{
				if(temp&0x80)TFT_DrawPoint(x+t2+8,y+t1,POINT_COLOR);//��һ����    
				temp<<=1;
			}  
		}
	}

      
	   
}

void Light_PWM(void){
  TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM4_OCInitStructure;
  TIM_BDTRInitTypeDef TIM4_BDTRInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  //ErrorStatus HSEStartUpStatus;
  
  //u16 CCR1_Val = 0xffff;   //PWM ռ�ձȵ���������  0xffff ��������    0x0  ����� 

  
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

 
  GPIO_PinRemapConfig(GPIO_Remap_TIM4 , ENABLE);


  TIM_DeInit(TIM4);

  /* Time Base configuration */
  TIM4_TimeBaseStructure.TIM_Prescaler = 0x00;
  TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM4_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM4_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM4_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

  TIM_TimeBaseInit(TIM4,&TIM4_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
  TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  //TIM4_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;                  
 // TIM4_OCInitStructure.TIM_Pulse = CCR1_Val; 
  TIM4_OCInitStructure.TIM_Pulse = 0x8000;//�����趨��0XFFFF������OX0000�
  TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
  TIM4_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;         
  TIM4_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM4_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;          
  
  TIM_OC2Init(TIM4,&TIM4_OCInitStructure); 

  

  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM4_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM4_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM4_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1; 
  TIM4_BDTRInitStructure.TIM_DeadTime = 0x75;
  TIM4_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM4_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM4_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM4,&TIM4_BDTRInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM4,ENABLE);

  /* Main Output Enable */
  //TIM_CtrlPWMOutputs(TIM4,ENABLE);
  //while(1);
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
