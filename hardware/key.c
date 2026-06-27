#include "key.h"
char key_value=0;//定义按键键值记录变量
char flag_kg=0;//定义系统开关状态变量。flag_kg=0关闭；flag_kg=1开启
char flag_ms=1;//定义小车模式变量。=1寻迹模式；=2避障模式；=3遥控模式
char car_speed_level=1;//=1一档；=2二档；=3三档

void key_init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_11;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //设置成上拉输入：识别GPIO口电平的变化
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO,ENABLE);//使能PORTC时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入：识别GPIO口电平的变化
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO,ENABLE);//使能PORTB时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入：识别GPIO口电平的变化
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);	
}

void key_scan(void)
{
  if(K1==0)//按键K1操作，实现系统开关
	{ 
		flag_kg++;if(flag_kg>1) flag_kg=0;
	  while(K1==0);//松手检测：防止误触发。 
	}
	if(K2==0)//按键K2用于调速
	{
	  while(K2==0);//松手检测
		flag_ms++;if(flag_ms>3) flag_ms=1;
	}
	if(K3==0)//按键K3用于设置模式
	{
	  while(K3==0);//松手检测
		car_speed_level++;if(car_speed_level>3) car_speed_level=1;
	}
	if(K4==0)//按键K3用于设置模式
	{
	  while(K4==0);//松手检测
	}
}

