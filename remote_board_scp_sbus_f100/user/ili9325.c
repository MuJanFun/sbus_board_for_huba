/* Includes ------------------------------------------------------------------*/
#include "ili9325.h"
#include "stm32f10x.h"	
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
/* Global variables to set the written text color */

vu16 TextColor = 0x0000, BackColor = 0xFFFF;
vu16 DeviceCode=0;
//******************************************************************************//
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : STM3210E_LCD_Init
* Description    : Initializes the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void STM3210E_LCD_Init(void)
{ 
  LCD_CtrlLinesConfig();/* Configure the LCD Control pins */
  Delay_ms(10);
  LCD_FSMCConfig();     /* Configure the FSMC Parallel interface */
  Delay_ms(20);
  LCD_RST_L();
  Delay_ms(10);
  LCD_RST_H();
  Delay_ms(50); /* delay 50 ms */

 
  

  //DeviceCode=LCD_ReadReg(0x0000);
	LCD_WriteReg(0x0000,0x0001);//打开晶振
	LCD_WriteReg(0x0010,0x0000);//退出休眠
//	delay_ms(50);
   //LCD_WriteReg(0x0001,0x2B3F);//竖屏显示
	LCD_WriteReg(0x0001,0x293F);//横屏显示
	LCD_WriteReg(0x0007,0x0033);//
	LCD_WriteReg(0x0011,0x6838);//横屏显示
//	LCD_WriteReg(0x0011,0x6830);//竖屏显示 

	LCD_WriteReg(0x0002,0x0600);
	/*gamma*/
	LCD_WriteReg(0x0030,0x0101);
	LCD_WriteReg(0x0031,0x0101);
	LCD_WriteReg(0x0032,0x0101);
	LCD_WriteReg(0x0033,0x0101);
	LCD_WriteReg(0x0034,0x0101);
	LCD_WriteReg(0x0035,0x0101);
	LCD_WriteReg(0x0036,0x0101);
	LCD_WriteReg(0x0037,0x0101);
	LCD_WriteReg(0x003A,0x0101);
	LCD_WriteReg(0x003B,0x0101);
	/*Pixel*/
	LCD_WriteReg(0x0044,0xEF00);
	LCD_WriteReg(0x0045,0x0000);
	LCD_WriteReg(0x0046,0x013F);
    Delay_ms(50);
}

/*******************************************************************************
* Function Name  : LCD_SetTextColor
* Description    : Sets the Text color.
* Input          : - Color: specifies the Text color code RGB(5-6-5).
* Output         : - TextColor: Text color global variable used by LCD_DrawChar
*                  and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetTextColor(vu16 Color)
{
  TextColor = Color;
}

/*******************************************************************************
* Function Name  : LCD_SetBackColor
* Description    : Sets the Background color.
* Input          : - Color: specifies the Background color code RGB(5-6-5).
* Output         : - BackColor: Background color global variable used by 
*                  LCD_DrawChar and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetBackColor(vu16 Color)
{
  BackColor = Color;
}

/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Clears the hole LCD.
* Input          : Color: the color of the background.
* Output         : None
* Return         : None
*******************************************************************************/
void  LCD_Clear(u16 Color)
{
  u16 index = 0;  
  LCD_SetWindow(0,0,319,239); 
  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < 7680; index++)
  {
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
    LCD->LCD_RAM = Color;
	//Delay_ms(2000);
  }  
}


/******************************************************************
*函数名  ：LCD_SetWindow(unsigned char,unsigned int,unsigned char ,unsigned int)
*入口参数: x0 y0,为显示窗口左上角坐标；x1,y1为显示窗口右下角坐标。
*出口参数: 无
*说明    ：该函数设置TFT模块的显示窗口。
******************************************************************/
void LCD_SetWindow(unsigned int y0,unsigned int x0,unsigned int y1,unsigned int x1)
{
LCD_WriteReg(0x0044,x0+(x1<<8));
LCD_WriteReg(0x0045,y0);
LCD_WriteReg(0x0046,y1);
LCD_SetCursor(y0,x0);
 

LCD_WriteRAM_Prepare();
}
/******************************************************************
*函数名  ：LCD_Draw_Point(unsigned char x,unsigned int y,unsigned int Data)
*入口参数: x y,为显示点坐标，Data为显示点颜色值。
*出口参数: 无
*说明    ：该函数为TFT模块的点显示函数。
******************************************************************/
void LCD_Draw_Point(unsigned char x,unsigned int y,unsigned int Data)
{
	LCD_WriteReg(0x0020,x);//设置X坐标位置
	LCD_WriteReg(0x0021,y);//设置Y坐标位置
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(Data);
}

/*******************************************************************************
* Function Name  : LCD_WindowModeDisable
* Description    : Disables LCD Window mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WindowModeDisable(void)
{
  LCD_SetWindow(239, 0x13F, 240, 320);
  LCD_WriteReg(0x03, 0x1018);    
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  /* Read 16-bit Reg */
  return (LCD->LCD_RAM);
}


/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = 0x22; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  LCD->LCD_RAM;
  return LCD->LCD_RAM;
}
/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
  /* Display On */
  LCD_WriteReg(0x07, 0x0173); /* 262K color and display ON */
}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
  /* Display Off */
  LCD_WriteReg(0x07, 0x0); 
}

//******************************************************************************//
//******************************************************************************//
//******************************************************************************//
//******************************************************************************//

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
                         RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
                         RCC_APB2Periph_AFIO, ENABLE);

  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as alternate 
     function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  GPIO_SetBits(GPIOG, GPIO_Pin_15 );
//***********************************************************************************
//                  根据需要自行添加的内容
//      GPIO_InitTypeDef GPIO_InitStructure;                //前面已经定义过
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* 推挽输出模式 */
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		GPIO_SetBits(GPIOF, GPIO_Pin_6);	                //开TFT背光

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* 推挽输出模式 */
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);              //TFT复位引脚
}
/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;

/*-- FSMC Configuration ------------------------------------------------------*/
  /* FSMC_Bank1_NORSRAM4 timing configuration */
  p.FSMC_AddressSetupTime =0;//1
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime =2;
  p.FSMC_BusTurnAroundDuration = 1;//0
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  /* FSMC_Bank1_NORSRAM4 configured as follows:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Disable
        - Asynchronous Wait = Disable */
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
 // FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  

  /* Enable FSMC_Bank1_NORSRAM4 */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);

}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
