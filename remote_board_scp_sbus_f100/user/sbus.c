
#include "include.h"

#define SBUS_CHANNEL_DEFAULT  7

#define SBUS_SCALE_FACTOR ((2000.0f - 1000.0f) / (1800.0f - 200.0f))
#define SBUS_SCALE_OFFSET ((int)(1000.0f - (((2000.0f - 1000.0f) / (1800.0f - 200.0f)) * 200.0f + 0.5f)))

__IO char flag_tac = 0; 

struct sbus_bit_pick {
	uint8_t byte;
	uint8_t rshift;
	uint8_t mask;
	uint8_t lshift;
};

/* sbus_decoder code */
static const struct sbus_bit_pick sbus_decoder[16][3] = {
	/*  0 */ { { 0, 0, 0xff, 0}, { 1, 0, 0x07, 8}, { 0, 0, 0x00,  0} },
	/*  1 */ { { 1, 3, 0x1f, 0}, { 2, 0, 0x3f, 5}, { 0, 0, 0x00,  0} },
	/*  2 */ { { 2, 6, 0x03, 0}, { 3, 0, 0xff, 2}, { 4, 0, 0x01, 10} },
	/*  3 */ { { 4, 1, 0x7f, 0}, { 5, 0, 0x0f, 7}, { 0, 0, 0x00,  0} },
	/*  4 */ { { 5, 4, 0x0f, 0}, { 6, 0, 0x7f, 4}, { 0, 0, 0x00,  0} },
	/*  5 */ { { 6, 7, 0x01, 0}, { 7, 0, 0xff, 1}, { 8, 0, 0x03,  9} },
	/*  6 */ { { 8, 2, 0x3f, 0}, { 9, 0, 0x1f, 6}, { 0, 0, 0x00,  0} },
	/*  7 */ { { 9, 5, 0x07, 0}, {10, 0, 0xff, 3}, { 0, 0, 0x00,  0} },
	/*  8 */ { {11, 0, 0xff, 0}, {12, 0, 0x07, 8}, { 0, 0, 0x00,  0} },
	/*  9 */ { {12, 3, 0x1f, 0}, {13, 0, 0x3f, 5}, { 0, 0, 0x00,  0} },
	/* 10 */ { {13, 6, 0x03, 0}, {14, 0, 0xff, 2}, {15, 0, 0x01, 10} },
	/* 11 */ { {15, 1, 0x7f, 0}, {16, 0, 0x0f, 7}, { 0, 0, 0x00,  0} },
	/* 12 */ { {16, 4, 0x0f, 0}, {17, 0, 0x7f, 4}, { 0, 0, 0x00,  0} },
	/* 13 */ { {17, 7, 0x01, 0}, {18, 0, 0xff, 1}, {19, 0, 0x03,  9} },
	/* 14 */ { {19, 2, 0x3f, 0}, {20, 0, 0x1f, 6}, { 0, 0, 0x00,  0} },
	/* 15 */ { {20, 5, 0x07, 0}, {21, 0, 0xff, 3}, { 0, 0, 0x00,  0} }
};

/* sbus decode */
int sbus_decode( uint16_t *values, uint8_t *frame_cache )
{
	static unsigned int frame_lost_cnt = 0;
	static unsigned char flag_lost = 0;
	unsigned channel = 0;
	unsigned value = 0;
	unsigned piece = 0;
	unsigned pick = 0;
	int i;
//  CPU_SR cpu_sr;
	
//	OS_CRITICAL_ENTER();

	if(!(frame_cache[0] == 0x0f && frame_cache[24] == 0))
	{
		for(i=0;i<7;i++)
		{
			values[i] = 0;
		}
		return 0;
	}
	
	
	/* use the decoder matrix to extract channel data */
	for (channel = 0; channel < SBUS_CHANNEL_DEFAULT; channel++)
	{
		value = 0;
    
		for ( pick = 0; pick < 3; pick++ ) 
		{
			const struct sbus_bit_pick *decode = &sbus_decoder[channel][pick];

			if (decode->mask != 0) 
			{
				piece = frame_cache[1 + decode->byte];
				piece >>= decode->rshift;
				piece &= decode->mask;
				piece <<= decode->lshift;

				value |= piece;
			}
		}
		/* convert 0-2048 values to 1000-2000 ppm encoding in a not too sloppy fashion */
    values[channel] = (uint16_t)(value * SBUS_SCALE_FACTOR + .5f) + SBUS_SCALE_OFFSET;
		
		if(values[channel]>1000)
		{
			values[channel] = values[channel] - 1000;
		}else
		{
			values[channel] = 0;
		}
	}
	
	if(frame_cache[23] & (1 << 2))
	{
		frame_lost_cnt++;
		if( frame_lost_cnt > 20 || flag_lost )
		{
			flag_lost = 1;
			for(i=0;i<7;i++)
			{
				values[i] = 0;
			}
		}
	}else
	{
		frame_lost_cnt = 0;
		flag_lost = 0;
	}

//	OS_CRITICAL_EXIT_NO_SCHED();
	
  return 0;
}
