#ifndef __JPEG_H__
#define __JPEG_H__
#endif

#include "tjpgd.h"

UINT in_func (JDEC* jd, BYTE* buff, UINT nbyte);
UINT out_func (JDEC* jd, void* bitmap, JRECT* rect);
void load_jpg(FIL*fp,void*work,u16 sz_work);
void load_bmp(FIL*fp,void*work,u16 sz_work);






















