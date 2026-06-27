#include "led.h"
#include "key.h"
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;				 //LED0-->PB.9 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出：可以设置成高电压或者低电压。用于驱动其他器件。
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.9
 GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);//SetBits将IO口设置为高电平。RestBits将IO口设置为1电平
}
/*
LED1=0 亮---系统开启 flag_kg=1
LED1=1 灭---系统关闭 flag_kg=0
LED2=1 LED3=0  模式1  寻迹模式  flag_ms=1
LED2=0 LED3=1  模式2  避障模式  flag_ms=2
LED2=0 LED3=0  模式3  遥控模式  flag_ms=3
*/


 
