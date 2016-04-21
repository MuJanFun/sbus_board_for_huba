#ifndef __SPI_H
#define __SPI_H

#define SPI_SPEED_2   0
#define SPI_SPEED_4   1
#define SPI_SPEED_8   2
#define SPI_SPEED_16  3
#define SPI_SPEED_32  4
#define SPI_SPEED_64  5
#define SPI_SPEED_128 6
#define SPI_SPEED_256 7
						  	    													  
void SPIx_Init(void);			 //��ʼ��SPI��
void SPIx_SetSpeed(unsigned char SpeedSet); //����SPI�ٶ�   
unsigned char SPIx_ReadWriteByte(unsigned char TxData);//SPI���߶�дһ���ֽ�
		 
#endif

