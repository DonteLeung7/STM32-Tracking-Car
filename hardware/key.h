#ifndef __KEY_H_
#define __KEY_H_
#include "stm32f10x.h"
#include "delay.h"
#include  "stdio.h"
//按键的GPIO口定义
#define K1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键1
#define K2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)//读取按键2 
#define K3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//读取按键3 
#define K4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//读取按键4 
//声明变量
extern char key_value;//定义按键键值记录变量
extern char flag_kg;//定义系统开关状态变量。flag_kg=0关闭；flag_kg=1开启
extern char flag_ms;//定义小车模式变量。=1寻迹模式；=2避障模式；=3遥控模式
extern char car_speed_level;//=1一档；=2二档；=3三档
//函数声控
void key_init(void); //IO初始化
void key_scan(void);//按键识别函数
#endif


