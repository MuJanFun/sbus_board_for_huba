
#include "include.h"

#include "ng_gpio.h"

#define DELAY_3MS 27050
#define DELAY_8MS 72128

void RCC_Configuration1(void);
void sbus_init(void);
void usart_send_init(void);
extern u8 frame[25];
u16 dsm_date[7]={0,0,0,0,0,0,0};

void delay_soft(unsigned int t)
{
	while(t--);
}

int main(void)
{
	int i;
	BSP_init();
  RCC_Configuration1();
  sbus_init();
	usart_send_init();
	printf("123sss\r\n"); 
  while(1)
  {
//	  delay_soft(DELAY_8MS);	//42+8=50ms	
		
		sbus_decode(dsm_date,frame);
		
    for(i=1;i<8;i++)
		{
	    delay_soft(DELAY_3MS);
			while(!((USART2->SR)&(1<<7)));
			USART2->DR = (dsm_date[i-1]>>5)|(i<<5);
			delay_soft(DELAY_3MS);
			while(!((USART2->SR)&(1<<7)));
			USART2->DR = (dsm_date[i-1]&0x1f)|(i<<5);
	  }
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif



/******************* (C) COPYRIGHT 2009  *****END OF FILE****/
