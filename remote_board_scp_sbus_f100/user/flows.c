#include "include.h"

__IO u8 f_data[64]; 
extern __IO  u8 rxdmas[22]; 
extern __IO u16 acefreqdata[10];
extern __IO u16 FreQ_public;
extern u16  step_ADJ_public;
float sflowstab[21]={0,7.80,16.78,25.00,32.77,41.28,
49.536,66.048,74.304,82.56,90.816,	 //49.536,66.048 ->46.47,57.1
99.072,107.328,115.584,123.84,132.096,
140.352,148.608,156.864,165.12,173.376};//step to 200,max to 1400 L/min

u16 getsflows(float freq)
{
   u8 i=7;
   if(freq>sflowstab[20]) return 4000;
   else{
   while(!(freq>=sflowstab[i--]));
   return  (u16)((u8)(i+1)*200+200*((freq-sflowstab[(u8)(i+1)])/(sflowstab[(u8)(i+2)]-sflowstab[(u8)(i+1)])));
   }
}

/*
 select  maxnum  of  nums
*/
u16 getfreq(void)
{
   u8 i,j;
   u8 set[10];
   u8 kmax=0;
   static u8 offset=0;
   for(i=0;i<10;i++)
   {
     for(j=0;j<10;j++)
	 {
	   	if(acefreqdata[i]==acefreqdata[j])
		{
		  set[i]++;
		}
	 }
   }
   kmax=set[0];
   for(i=0;i<10;i++)
   {
     if(kmax<set[i]) 
	 {
	   kmax=set[i];
	   offset=i;
	 }
   }
  return  acefreqdata[offset];
}




void updatabuffer(u8 steps,u16 total,u16 sflows_f,u8 press_f)
{
  f_data[0]=steps+'0';
  f_data[1]=' ';
  f_data[2]=' ';
  f_data[3]=' ';
  f_data[4]=' ';
  f_data[5]='2';
  f_data[6]='0';
  f_data[7]=rxdmas[6]/16+'0';  //年
  f_data[8]=rxdmas[6]%16+'0';
  f_data[9]='-';
  f_data[10]=rxdmas[7]/16+'0';	//月
  f_data[11]=rxdmas[7]%16+'0';
  f_data[12]='-';
  f_data[13]=rxdmas[8]/16+'0';	//日
  f_data[14]=rxdmas[8]%16+'0';
  f_data[15]=' ';
  f_data[16]=rxdmas[10]/16+'0';	//时
  f_data[17]=rxdmas[10]%16+'0';
  f_data[18]=':';
  f_data[19]=rxdmas[11]/16+'0';	//分
  f_data[20]=rxdmas[11]%16+'0';
  f_data[21]=':';
  f_data[22]=rxdmas[12]/16+'0';
  f_data[23]=rxdmas[12]%16+'0';
  f_data[24]=' ';
  f_data[25]=' ';
  f_data[26]=' ';
  f_data[27]=' ';
  f_data[28]=sflows_f/1000+'0';	//瞬时流量
  f_data[29]=sflows_f%1000/100+'0';
  f_data[30]=sflows_f%100/10+'0';
  f_data[31]=sflows_f%10+'0';
  f_data[32]='L';
  f_data[33]='/';
  f_data[34]='m';
  f_data[35]='i';
  f_data[36]='n';
  f_data[37]=' ';
  /*f_data[38]=FreQ_public/1000+'0';
  f_data[39]=FreQ_public%1000/100+'0';
  f_data[40]=FreQ_public%100/10+'0';
  f_data[41]=FreQ_public%10+'0'; */
  f_data[38]=' ';
  f_data[39]=' ';
  f_data[40]=' ';
  f_data[41]=' ';
  f_data[42]=' ';
  f_data[43]=total/10000+'0';
  f_data[44]=total%10000/1000+'0';
  f_data[45]=total%1000/100+'0';
  f_data[46]='.';
  f_data[47]=total%100/10+'0';
  f_data[48]=total%10+'0';
  f_data[49]='M';
  f_data[50]=' ';
  f_data[51]=step_ADJ_public/100+'0';
  f_data[52]=step_ADJ_public%100/10+'0';
  f_data[53]=step_ADJ_public%10+'0';
  //f_data[51]=' ';
  //f_data[52]=' ';
 // f_data[53]=' ';
  f_data[54]=' ';
  f_data[55]=press_f/100+'0';
  f_data[56]=press_f%100/10+'0';
  f_data[57]='.';
  f_data[58]=press_f%10+'0';
  f_data[59]='M';
  f_data[60]='p';
  f_data[61]='a';
  f_data[62]=0x0d;
  f_data[63]=0x0a;
}

















