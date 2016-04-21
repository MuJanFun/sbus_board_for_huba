#include "spi.h"
#include"stm32f10x.h"
void SPIx_Init(void)
{	 
	
	SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
   
  /* ʹ��VS1003B����I/O��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* ʹ��SPI2 ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);
		
  /* ���� SPI2 ����: PB13-SCK, PB14-MISO �� PB15-MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* SPI2 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				  	
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;			  	
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				  		
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				  
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  	SPI2->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
  /* Enable SPI2  */
  SPI_Cmd(SPI2, ENABLE);   									  	 		 
}   
//SPI �ٶ����ú���
//SpeedSet:
//SPI_SPEED_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_SPEED_4   4��Ƶ   (SPI 18M@sys 72M)
//SPI_SPEED_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_SPEED_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_SPEED_256 256��Ƶ (SPI 281.25K@sys 72M)
void SPIx_SetSpeed(unsigned char SpeedSet)
{
	SPI2->CR1&=0XFFC7;//Fsck=Fcpu/256
	switch(SpeedSet)
	{
		case SPI_SPEED_2://����Ƶ
			SPI2->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz
			break;
		case SPI_SPEED_4://�ķ�Ƶ
			SPI2->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
			break;
		case SPI_SPEED_8://�˷�Ƶ
			SPI2->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz
			break;
		case SPI_SPEED_16://ʮ����Ƶ
			SPI2->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
			break;
		case SPI_SPEED_32:  //32��Ƶ
			SPI2->CR1|=4<<3;//Fsck=Fpclk/32=2.25Mhz
			break;
		case SPI_SPEED_64:  //64��Ƶ
			SPI2->CR1|=5<<3;//Fsck=Fpclk/16=1.125Mhz
			break; 
		case SPI_SPEED_128: //128��Ƶ
			SPI2->CR1|=6<<3;//Fsck=Fpclk/16=562.5Khz
			break;
		case SPI_SPEED_256: //256��Ƶ
			SPI2->CR1|=7<<3;//Fsck=Fpclk/16=281.25Khz
			break;
	}		 
	SPI2->CR1|=1<<6; //SPI�豸ʹ��	  
} 
//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�

unsigned char SPIx_ReadWriteByte(unsigned char byte)
{						 
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);		// �ж�SPI1 ���ͻ������Ƿ��  
  SPI_I2S_SendData(SPI2, byte);											                // ����8λ����
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	  // �ж��Ƿ���ջ������ǿ�
  return SPI_I2S_ReceiveData(SPI2);		    
}































