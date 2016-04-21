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

#define	CMD_GET_STATUS		0x22			/* ��ȡ�ж�״̬��ȡ���ж����� */

#define	CMD_DISK_INIT		0x51			/* ������ʽ: ��ʼ��USB�洢�� */

#define	CMD_DISK_READ		0x54			/* ������ʽ: ��USB�洢�������ݿ�(������Ϊ��λ) */

#define	CMD_RD_USB_DATA		0x28			/* �ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�, 
���ͷŻ�����, �൱�� CMD_RD_USB_DATA0 + CMD_UNLOCK_USB */
#define	CMD_DISK_RD_GO		0x55			/* ������ʽ: ����ִ��USB�洢���Ķ����� */

#define	CMD_DISK_WRITE		0x56			/* ������ʽ: ��USB�洢��д���ݿ�(������Ϊ��λ) */

#define	CMD_WR_USB_DATA7	0x2B			/* ��USB�˵�2���������˵�ķ��ͻ�����д�����ݿ� */

#define	CMD_DISK_WR_GO		0x57			/* ������ʽ: ����ִ��USB�洢����д���� */

#define	CMD_SET_USB_MODE	0x15			/* ����USB����ģʽ */

#define	CMD_RET_ABORT		0x5F			/* �������ʧ�� */

#define	CMD_RET_SUCCESS		0x51			/* ��������ɹ� */

/* ����״̬����1XH����USB������ʽ�Ĳ���״̬����, ��CH375֧�� */
#ifndef	USB_INT_SUCCESS
#define	USB_INT_SUCCESS		0x14			/* USB������ߴ�������ɹ� */
#define	USB_INT_CONNECT		0x15			/* ��⵽USB�豸�����¼� */
#define	USB_INT_DISCONNECT	0x16			/* ��⵽USB�豸�Ͽ��¼� */
#define	USB_INT_BUF_OVER	0x17			/* USB���ƴ��������̫��, ��������� */
#define	USB_INT_USB_READY	0x18			/* USB�豸�Ѿ�����ʼ�����ѷ���USB��ַ�� */
#define	USB_INT_DISK_READ	0x1D			/* USB�洢�������ݿ�, �������ݶ��� */
#define	USB_INT_DISK_WRITE	0x1E			/* USB�洢��д���ݿ�, ��������д�� */
#define	USB_INT_DISK_ERR	0x1F			/* USB�洢������ʧ�� */
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
