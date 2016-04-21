#ifndef __USART_H__
#define __USART_H__

#define RxEN   1     //define RxEN to select the function of Rx
#define RxDMA  1

#define battery 0x00
#define sflows  0x02
#define press_p	0x04
#define lflows  0x06
#define press   0x08
#define qflows  0x0a 
#define nflows  0x0c
#define tflows  0x0e
#define qflash  0x10
#define nflash  0x12
#define tflash  0x14
#define FreQ    0x16

#define minute_cnt 0x18

typedef struct rextxb{

u8 rexb[5];
u8 temp;
u8 rex0;
u8 rex1;

}TxCpy;

void uart2_init(u32 bound);
void uart_init(u32 pclk2,u32 bound);
void NoUsartDMAEnable(TxCpy *fp,u8 mode,u16 data);
void Uart3_Init(u32 br_num);
 void GPIO_Configuration(void);
void USART3_Configuration(void) ;                   
 void RCC_Configuration(void);
void USART_Configuration(u32 BaudRate);                    

#endif

