#ifndef __BSP_H__
#define __BSP_H__

#include "include.h"



typedef enum{

BSP_Init_OK = 0,

BSP_Init_ERROR = 1

}BSPRESULT;

void BSP_init(void);


#endif

