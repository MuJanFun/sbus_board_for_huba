#ifndef __VS10XX_H__
#define __VS10XX_H__

//VS10xx���ⲿ�ӿڶ���(δ����MISO,MOSI,SCK)
// PB5.6.8 ��� PB7 ����
#define VS_CFG      GPIOB->CRL&=0x000fffff;GPIOB->CRL|=0x83300000;GPIOB->CRH&=0xfffffff0;GPIOB->CRH|=0x00000003

#define VS_DREQ     ((GPIOB->IDR&(1<<7)))
#define VS_DREQ_SET     GPIOB->ODR|=1<<7
#define VS_DREQ_CLR     GPIOB->ODR&=~(1<<7)

#define VS_XRESET_SET   GPIOB->ODR|=1<<6
#define VS_XRESET_CLR   GPIOB->ODR&=~(1<<6)
      
#define VS_XCS_SET      GPIOB->ODR|=1<<5
#define VS_XCS_CLR      GPIOB->ODR&=~(1<<5)

#define VS_XDCS_SET     GPIOB->ODR|=1<<8
#define VS_XDCS_CLR     GPIOB->ODR&=~(1<<8)

							 


//����					  
#define VS_WRITE_COMMAND 	0x02  //д����
#define VS_READ_COMMAND 	0x03  //������
//VS10XX�Ĵ�������
#define VS_MODE        	0x00  //ģʽ����   
#define VS_STATUS      	0x01  //VS10XX��״̬�Ĵ��� 
#define VS_BASS        	0x02  //�ߵ������� 
#define VS_CLOCKF      	0x03  //ʱ��Ƶ�ʱ��˼Ĵ��� 
#define VS_DECODE_TIME 	0x04  //����ʱ�䳤�� 
#define VS_AUDATA      	0x05  //������Ƶ���� 
#define VS_WRAM        	0x06  //RAM д/�� 
#define VS_WRAMADDR    	0x07  //RAM д/������ʼ��ַ 
#define VS_HDAT0       	0x08  //�����ݱ�ͷ0 
#define VS_HDAT1       	0x09  //�����ݱ�ͷ1	 
   
#define VS_AIADDR      	0x0a  //Ӧ�ó������ʼ��ַ 
#define VS_VOL         	0x0b  //�������� 
#define VS_AICTRL0     	0x0c  //Ӧ�ó�����ƼĴ���0 
#define VS_AICTRL1     	0x0d  //Ӧ�ó�����ƼĴ���1 
#define VS_AICTRL2     	0x0e  //Ӧ�ó�����ƼĴ���2 
#define VS_AICTRL3     	0x0f  //Ӧ�ó�����ƼĴ���3
//SPI_MODE�ĸ�λ����,�±����VS1053���ֲ��ע
#define SM_DIFF         	0x01  //��� 
#define SM_LAYER12         	0x02  //����MPEG 1,2���� FOR vs1053 
#define SM_RESET        	0x04  //�����λ 
#define SM_CANCEL       	0x08  //ȡ����ǰ���� 
#define SM_EARSPEAKER_LO  	0x10  //EarSpeaker���趨 
#define SM_TESTS        	0x20  //����SDI���� 
#define SM_STREAM       	0x40  //��ģʽ 
#define SM_EARSPEAKER_HI   	0x80  //EarSpeaker���趨  
#define SM_DACT         	0x100 //DCLK����Ч����  
#define SM_SDIORD       	0x200 //SDIλ˳��  
#define SM_SDISHARE     	0x400 //����SPIƬѡ  
#define SM_SDINEW       	0x800 //VS1002 ����SPIģʽ  
#define SM_ADPCM        	0x1000//ADPCM¼������   
#define SM_LINE1         	0x4000//��/��·1 ѡ�� 		 
#define SM_CLK_RANGE     	0x8000//����ʱ�ӷ�Χ 	
	 

void VS_Write_Reg(unsigned char addr,unsigned int dat);
unsigned int VS_Read_Reg(unsigned char addr);
void VS_Reset(void);
void VS_Send_Dat(unsigned char Dat);
void VS_sin_test(unsigned char x);
void VS_Flash_Buffer(void);


#endif














			  
















