#ifndef __CH375_H__
#define __CH375_H__

#include"include.h"
/*--------------------------------------------/
/  CH375.h Bottom Drivers And FatFs defines
/---------------------------------------------/
/											  /
/											  /
/											  /
/											  /
/---------------------------------------------*/

#define	CMD_GET_STATUS		0x22			/* 获取中断状态并取消中断请求 */

#define	CMD_DISK_INIT		0x51			/* 主机方式: 初始化USB存储器 */

#define	CMD_DISK_READ		0x54			/* 主机方式: 从USB存储器读数据块(以扇区为单位) */

#define	CMD_RD_USB_DATA		0x28			/* 从当前USB中断的端点缓冲区读取数据块, 
并释放缓冲区, 相当于 CMD_RD_USB_DATA0 + CMD_UNLOCK_USB */
#define	CMD_DISK_RD_GO		0x55			/* 主机方式: 继续执行USB存储器的读操作 */

#define	CMD_DISK_WRITE		0x56			/* 主机方式: 向USB存储器写数据块(以扇区为单位) */

#define	CMD_WR_USB_DATA7	0x2B			/* 向USB端点2或者主机端点的发送缓冲区写入数据块 */

#define	CMD_DISK_WR_GO		0x57			/* 主机方式: 继续执行USB存储器的写操作 */

#define	CMD_SET_USB_MODE	0x15			/* 设置USB工作模式 */

#define	CMD_RET_ABORT		0x5F			/* 命令操作失败 */

#define	CMD_RET_SUCCESS		0x51			/* 命令操作成功 */

/* 以下状态代码1XH用于USB主机方式的操作状态代码, 仅CH375支持 */
#ifndef	USB_INT_SUCCESS
#define	USB_INT_SUCCESS		0x14			/* USB事务或者传输操作成功 */
#define	USB_INT_CONNECT		0x15			/* 检测到USB设备连接事件 */
#define	USB_INT_DISCONNECT	0x16			/* 检测到USB设备断开事件 */
#define	USB_INT_BUF_OVER	0x17			/* USB控制传输的数据太多, 缓冲区溢出 */
#define	USB_INT_USB_READY	0x18			/* USB设备已经被初始化（已分配USB地址） */
#define	USB_INT_DISK_READ	0x1D			/* USB存储器读数据块, 请求数据读出 */
#define	USB_INT_DISK_WRITE	0x1E			/* USB存储器写数据块, 请求数据写入 */
#define	USB_INT_DISK_ERR	0x1F			/* USB存储器操作失败 */
#endif





#define UWR_SET GPIOC->ODR|=1<<7
#define UWR_CLR GPIOC->ODR&=~(1<<7)

#define URD_SET GPIOC->ODR|=1<<8
#define URD_CLR GPIOC->ODR&=~(1<<8)

#define URX_SET GPIOC->ODR|=1<<9
#define URX_CLR GPIOC->ODR&=~(1<<9)

#define UA0_SET GPIOA->ODR|=1<<8
#define UA0_CLR GPIOA->ODR&=~(1<<8)

#define UCS_SET GPIOA->ODR|=1<<11
#define UCS_CLR GPIOA->ODR&=~(1<<11)

#define UD8_OUT GPIOB->CRH=0x33333333
#define UD8_IN  GPIOB->CRH=0x88888888;GPIOB->ODR|=0xff00

#define UD8(x)  GPIOB->ODR&=0x00ff;GPIOB->ODR|=x<<8 
#define UD8_STA	(GPIOB->IDR)>>8

#define UINT_STA !!(GPIOC->IDR&(1<<6))


typedef enum{ 

UFR_OK = 0, 

UFR_ERROR = 1,

USB_DISK_ERROR = 1,

USB_DISK_OK = 0

}UFRESULT;
/*--------------------Functions-----------*/
u8 sw(u8 dat);
void ch375_io_configration(void);
u8 ch375_init(void);
u8 ch375_read(void);
UFRESULT ch375_initdisk(void);
u8 ch375ReadSector(u32 addr,u8 *data,u8 count);
u8 ch375WriteSector(u32 addr,const u8 *data,u8 count);

#endif
