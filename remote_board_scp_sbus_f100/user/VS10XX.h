#ifndef __VS10XX_H__
#define __VS10XX_H__

//VS10xx与外部接口定义(未包含MISO,MOSI,SCK)
// PB5.6.8 输出 PB7 输入
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

							 


//命令					  
#define VS_WRITE_COMMAND 	0x02  //写命令
#define VS_READ_COMMAND 	0x03  //读命令
//VS10XX寄存器定义
#define VS_MODE        	0x00  //模式控制   
#define VS_STATUS      	0x01  //VS10XX的状态寄存器 
#define VS_BASS        	0x02  //高低音控制 
#define VS_CLOCKF      	0x03  //时钟频率倍乘寄存器 
#define VS_DECODE_TIME 	0x04  //解码时间长度 
#define VS_AUDATA      	0x05  //各种音频数据 
#define VS_WRAM        	0x06  //RAM 写/读 
#define VS_WRAMADDR    	0x07  //RAM 写/读的起始地址 
#define VS_HDAT0       	0x08  //流数据标头0 
#define VS_HDAT1       	0x09  //流数据标头1	 
   
#define VS_AIADDR      	0x0a  //应用程序的起始地址 
#define VS_VOL         	0x0b  //音量控制 
#define VS_AICTRL0     	0x0c  //应用程序控制寄存器0 
#define VS_AICTRL1     	0x0d  //应用程序控制寄存器1 
#define VS_AICTRL2     	0x0e  //应用程序控制寄存器2 
#define VS_AICTRL3     	0x0f  //应用程序控制寄存器3
//SPI_MODE的各位功能,下表根据VS1053的手册标注
#define SM_DIFF         	0x01  //差分 
#define SM_LAYER12         	0x02  //允许MPEG 1,2解码 FOR vs1053 
#define SM_RESET        	0x04  //软件复位 
#define SM_CANCEL       	0x08  //取消当前解码 
#define SM_EARSPEAKER_LO  	0x10  //EarSpeaker低设定 
#define SM_TESTS        	0x20  //允许SDI测试 
#define SM_STREAM       	0x40  //流模式 
#define SM_EARSPEAKER_HI   	0x80  //EarSpeaker高设定  
#define SM_DACT         	0x100 //DCLK的有效边沿  
#define SM_SDIORD       	0x200 //SDI位顺序  
#define SM_SDISHARE     	0x400 //共享SPI片选  
#define SM_SDINEW       	0x800 //VS1002 本地SPI模式  
#define SM_ADPCM        	0x1000//ADPCM录音激活   
#define SM_LINE1         	0x4000//咪/线路1 选择 		 
#define SM_CLK_RANGE     	0x8000//输入时钟范围 	
	 

void VS_Write_Reg(unsigned char addr,unsigned int dat);
unsigned int VS_Read_Reg(unsigned char addr);
void VS_Reset(void);
void VS_Send_Dat(unsigned char Dat);
void VS_sin_test(unsigned char x);
void VS_Flash_Buffer(void);


#endif














			  
















