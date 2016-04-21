#include "include.h"
__IO u8 test,test1;
__IO u8 sws[256];

extern __IO u8 trytime;
void ch375_io_configration(void)
{
  u16 i;
  RCC->APB2ENR|=1<<2;//enable gpioa clock
  GPIOA->CRH&=0xffff0ff0;//
  GPIOA->CRH|=0x00003003;//PA8,PA11 output for pull

  RCC->APB2ENR|=1<<4;//enable gpioc clock
  GPIOC->CRL&=0x00ffffff;
  GPIOC->CRL|=0x38000000;	//PC6 InPut for pull

  GPIOC->CRH&=0xfffffff0;
  GPIOC->CRH|=0x00000003;//PC7,PC8,PC9 output for pull

  RCC->APB2ENR|=1<<3;//enable gpiob clock
  for(i=0;i<256;i++)
  {
    sws[i]=sw(i);
  }
  
}
void Delay_ss(u32 t)
{
 while(t--);
}
u8 sw(u8 dat)
{
  u8 i;
  u8 bdat=0;
  for(i=0;i<8;i++)
  {
    bdat|=(!!((dat<<i)&0x80))<<i;
  }
  return bdat;
}
static void ch375_write_cmd(u8 dat)
{
   UD8_OUT;
   Delay_us(40);
   UCS_CLR;
   Delay_us(40);
   UA0_SET;
   Delay_us(40);
   UD8(sws[dat]);
   Delay_us(40);
   UWR_CLR;
   Delay_us(40);
   UWR_SET;
   Delay_us(40);
   UCS_SET;
   Delay_us(40);
   UA0_SET;
   Delay_us(40);
}

static void ch375_write_dat(u8 dat)
{
   UD8_OUT;
   Delay_us(40);
   UCS_CLR;
   Delay_us(40);
   UA0_CLR;
   Delay_us(40);
   UD8(sws[dat]);
   Delay_us(40);
   UWR_CLR;
   Delay_us(40);
   UWR_SET;
   Delay_us(40);
   UCS_SET;
   Delay_us(40);
   UA0_SET;
   Delay_us(40);
}
u8 ch375_read(void)
{
   u8 buffer;
   u16 sta;
   Delay_us(40);
   UD8_IN;
   Delay_us(40);
   UCS_CLR;
   Delay_us(40);
   UA0_CLR;
   Delay_us(40);
   URD_CLR;
   Delay_us(40);
   sta=GPIOB->IDR;
   Delay_us(40);
   buffer=sta>>8;
   Delay_us(40);
   URD_SET;
   Delay_us(40);
   UCS_SET;
   Delay_us(40);
   UA0_SET;
   Delay_us(40);
   return sws[buffer];
}

u8 ch375_init(void)
{
  //ch375_write_cmd(0x05);//hardware reset
  Delay_ms(80);
  ch375_write_cmd(CMD_SET_USB_MODE); //set usb mode
  Delay_us(10);
  ch375_write_dat(6);//auto check usb device
  Delay_us(20);
  test=ch375_read();
  if(test==CMD_RET_SUCCESS) return 0;
  else return 1;
}

static u8 ch375_wait_int(void)
{
  trytime=0;
  while((UINT_STA)&&(trytime<5));// get clr interrupt
  //DISENABLETIM2;
  if(trytime>5) return 0;
  //ENABLETIM2;
  ch375_write_cmd(CMD_GET_STATUS);
  return ch375_read();
}

UFRESULT ch375_initdisk(void)
{
  static u8 status1;
  status1=ch375_wait_int();
  if(status1!=USB_INT_CONNECT) return USB_DISK_ERROR; 
  ch375_write_cmd(CMD_DISK_INIT);
  status1=ch375_wait_int();
  if(status1!=USB_INT_SUCCESS) return USB_DISK_ERROR;
  Delay_ms(200);
  return USB_DISK_OK;
}

u8 ch375ReadSector(u32 addr,u8 *data,u8 count)
{
  u16 i=0;
  u8 j=0;
  u8 status,len;
  ch375_write_cmd(CMD_DISK_READ);
  ch375_write_dat(addr);
  ch375_write_dat(addr>>8);
  ch375_write_dat(addr>>16);
  ch375_write_dat(addr>>24);
  ch375_write_dat(count);  //how much setors to read=?
  for(i=0;i<8*count;i++)
  {				   
    status=status=ch375_wait_int();
  	if(status==USB_INT_DISK_READ)
	{
	 ch375_write_cmd(CMD_RD_USB_DATA);
	 len=ch375_read();
	 for(j=0;j<len;j++)
	 {
	   *data=ch375_read();
	   data++;
	 }
	 ch375_write_cmd(CMD_DISK_RD_GO);
	}
	else
	{
	   return 1;
	}
  }
  status=ch375_wait_int();
  if(status==USB_INT_SUCCESS) return 0;
  else return status;
}

u8 ch375WriteSector(u32 addr,const u8 *data,u8 count)
{
   u16 i;
   static u8 j;
   static u8 status2;
   ch375_write_cmd(CMD_DISK_WRITE);
   ch375_write_dat(addr);
   ch375_write_dat(addr>>8);
   ch375_write_dat(addr>>16);
   ch375_write_dat(addr>>24);
   ch375_write_dat(count);
  for(i=0;i<8*count;i++)
  {
    status2=ch375_wait_int();
  	if(status2==USB_INT_DISK_WRITE)
	{
	 ch375_write_cmd(CMD_WR_USB_DATA7);
	 ch375_write_dat(64);
	 for(j=0;j<64;j++)
	 {
	   ch375_write_dat(*data);
	   data++;
	 }
	 ch375_write_cmd(CMD_DISK_WR_GO);
	}
	else
	{
	   return 1;
	}
  }
  //status=ch375_wait_int();
  if(status2==0x1E) return 0;
  else return status2;
}










