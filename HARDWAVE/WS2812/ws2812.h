#ifndef __WS2812_H
#define __WS2812_H		
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"	
#include "math.h"

void WS2812_init(void);
void WS2812_send(uint8_t (*color)[3], uint16_t len);
u32 ColorToColor(unsigned long color0, unsigned long color1);
void Light_Ring_dirc(u8 direction);
void Light_Ring_deg(float degree);
void Light_Ring_RT(u8 *temp,u8 *humi);
#endif
