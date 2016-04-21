#ifndef _ILI9325_H_
#define _ILI9325_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Includes ------------------------------------------------------------------*/

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define Horizontal     0x00
#define Vertical       0x01
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  vu16 LCD_REG;
  vu16 LCD_RAM;
} LCD_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM4 and NE4 is used as ship select signal */
#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
#define LCD         ((LCD_TypeDef *) LCD_BASE)

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/                              

//************************************************************************************************************// 
//                      含参宏定义区
//************************************************************************************************************// 
/*******************************************************************************
* Name           : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/  
#define LCD_WriteReg(LCD_Reg,LCD_RegValue)	{LCD->LCD_REG = LCD_Reg;LCD->LCD_RAM = LCD_RegValue;}


/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
#define LCD_WriteRAM(RGB_Code) {LCD->LCD_RAM = RGB_Code;}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#define LCD_WriteRAM_Prepare()	{LCD->LCD_REG = 0x22;}

                               /* Write 16-bit GRAM Reg */
/*******************************************************************************
* Name           : LCD_RST_L()
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
#define LCD_RST_L()	{GPIO_ResetBits(GPIOG,GPIO_Pin_15);} //拉低复位引脚
/*******************************************************************************
* Name           : LCD_RST_H()
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
#define LCD_RST_H()	{GPIO_SetBits(GPIOG,GPIO_Pin_15);}   //置高复位引脚

/*******************************************************************************
* Name           : LCD_SetCursor(Xpos,Ypos)
* Description    : 设置光标位置
* Input          : Xpos:横坐标,Ypos:纵坐标
* Output         : None
* Return         : None
*******************************************************************************/
#define LCD_SetCursor(Xpos,Ypos){LCD_WriteReg(0x004f, Xpos);LCD_WriteReg(0x004e, Ypos);}


//************************************************************************************************************// 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/
extern void STM3210E_LCD_Init(void);
extern void LCD_SetTextColor(vu16 Color);
extern void LCD_SetBackColor(vu16 Color);
extern void LCD_Clear(u16 Color);
extern void LCD_WindowModeDisable(void);


/*----- Medium layer function -----*/

extern u16  LCD_ReadReg(u8 LCD_Reg);
extern u16  LCD_ReadRAM(void);
extern void LCD_DisplayOn(void);
extern void LCD_DisplayOff(void);
extern void LCD_Draw_Point(unsigned char x,unsigned int y,unsigned int Data);
extern void LCD_SetWindow(unsigned int y0,unsigned int x0,unsigned int y1,unsigned int x1);


/*----- Low layer function -----*/
extern void LCD_CtrlLinesConfig(void);
extern void LCD_FSMCConfig(void);

#endif /* _LCD_H_ */

/******************* (C) COPYRIGHT 2008 STMicroelectronics*/ 
/*****END OF FILE****/
