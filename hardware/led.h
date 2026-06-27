#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//LED灯的GPIO口定义
#define LED1 PBout(3)
#define LED2 PBout(4)
#define LED3 PBout(5)
//函数申明
void LED_Init(void);//初始化 	
#endif
