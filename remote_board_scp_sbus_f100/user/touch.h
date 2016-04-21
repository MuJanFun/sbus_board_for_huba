
#define __TOUCH_H  
//��������ʼ��
//ʹ���ⲿ8M����,PLL��72MƵ��		    

//2008/12/14 
//V1.0  

/*-------------------------------
�ܽŶ�Ӧ
PC.1 PEN
PC.2 DIN
PC.3 CLK
PB.8 CS
PB.9 DOUT
//ADS7846���¶Ȳ�����ѹ����������
//���Բο�PDF�����Լ�д	 
--------------------------------*/
#define DOUT GPIOA->IDR&1<<6 //PA6��������
			 
#define PEN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)   //PB6  	

#define NPEN !(0x01&PEN)     //!PEN	

 
#define TDIN  (1<<7)  // PA7
#define TCLK  (1<<5)  // PA5
#define TCS   (1<<7)  // PB7   			    
#define TDIN_SET(x) GPIOA->ODR=(GPIOA->ODR&~TDIN)|(x ? TDIN:0)
#define TCLK_SET(x) GPIOA->ODR=(GPIOA->ODR&~TCLK)|(x ? TCLK:0)													    
#define TCS_SET(x)  GPIOB->ODR=(GPIOB->ODR&~TCS)|(x ? TCS:0)  

//�ʸ˽ṹ��
typedef struct 
{
	u16 X0;//ԭʼ����
	u16 Y0;
	u16 X; //����/�ݴ�����
	u16 Y;						   	    
	u8  Key_Sta;//�ʵ�״̬
	u8  Key_LSta;//��һ�αʵ�״̬
//������У׼����
	float xfac;
	float yfac;
	short xoff;
	short yoff;
}Pen_Holder;



//����״̬	 
#define Key_Down 0x01
#define Key_Up   0x00 
//��������������
#define CLICK_POINT 0X01   
#define MOVE_LEFT   0X10
#define MOVE_RIGHT  0X20
#define MOVE_UP     0X40
#define MOVE_DOWN   0X80

//TFTLCD������ɫ�Ķ���		
#define RED	  0XF800
#define GREEN 0X07E0
#define BLUE  0X001F  
#define BRED  0XF81F
#define GRED  0XFFE0
#define GBLUE 0X07FF
#define WHITE 0XFFFF //��ɫ
#define BLACK 0X0000 //��ɫ
#define BROWN 0XBC40 //��ɫ
#define BRRED 0XFC07 //�غ�ɫ
#define GRAY  0X8430 //��ɫ
#define LGRAY 0XC618 //ǳ��ɫ


