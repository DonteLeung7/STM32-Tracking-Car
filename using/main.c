#include "main.h"


//串口1蓝牙程序代码
/*串口接收识别的蓝牙串口指令格式（十六进制）：
30 0D 0A --0
31 0D 0A --1
32 0D 0A --2
33 0D 0A --3
34 0D 0A --4
APP发送时，定义以上十六进制编码

*/
//Port
#define Bluetooth_Port GPIOA
//Pin
#define Bluetooth_TXD_Pin GPIO_Pin_9
#define Bluetooth_RXD_Pin GPIO_Pin_10
uint8_t Bluetooth_Receive_Buffer[200];//接收缓存数组
uint16_t Bluetooth_Buffer_Address=0;//接收状态标记
void Bluetooth_Config(uint32_t baud) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// TX PA9
	GPIO_InitStructure.GPIO_Pin = Bluetooth_TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

// RX PA10
	GPIO_InitStructure.GPIO_Pin = Bluetooth_RXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=baud;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

u8 car_zhiling=0;
void USART1_IRQHandler(void) {
	char c;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		c = USART_ReceiveData(USART1);

		if(c == '2')
			car_zhiling = 2;   // 前进

		else if(c == '8')
			car_zhiling = 8;   // 后退

		else if(c == '4')
			car_zhiling = 4;   // 左转

		else if(c == '6')
			car_zhiling = 6;   // 右转

		else if(c == '5')
			car_zhiling = 5;   // 停止
	}
}


void xianshi(void) {

}


#include "OLED.h"

u16 sd_value=0;
u32 JL=0;
int main() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_Config();//时钟初始化
	SystemInit();//初始化系统时钟为72MHZ
	key_init();
	TIM3_PWM_Init();
	CGQ_Init();
	LED_Init();
	LED1=LED2=LED3=1;
	delay_init();	    	 //延时函数初始化
	Bluetooth_Config(9600);
	Hcsr04Init();
	OLED_Init();
	OLED_Clear();

	while(1) {
		key_scan();//键盘识别获取键值
		//速度选择
		if(car_speed_level==1) sd_value=770;
		else if(car_speed_level==2) sd_value=785;
		else if(car_speed_level==3) sd_value=820;


		//第一行显示：智能小车设计
		OLED_P16x16Ch_2(16,0,0);
		OLED_P16x16Ch_2(32,0,1);
		OLED_P16x16Ch_2(48,0,2);
		OLED_P16x16Ch_2(64,0,3);
		OLED_P16x16Ch_2(80,0,4);
		OLED_P16x16Ch_2(96,0,5);
		//第二行显示：开关
		OLED_P16x16Ch_2(0,2,6);
		OLED_P16x16Ch_2(16,2,7);
		OLED_ShowString(32,2,":",16);
		if(flag_kg==0) {
			LED1=1;    //关
			OLED_P16x16Ch_2(48,2,9);
		}
		if(flag_kg==1) {
			LED1=0;    //开
			OLED_P16x16Ch_2(48,2,8);
		}
		//第三行显示：模式
		OLED_P16x16Ch_2(0,4,10);
		OLED_P16x16Ch_2(16,4,11);
		OLED_ShowString(32,4,":",16);
		if(flag_ms==1) {
			LED2=1;
			LED3=0;
			OLED_P16x16Ch_2(48,4,14);
			OLED_P16x16Ch_2(64,4,15);
		}
		if(flag_ms==2) {
			LED2=0;
			LED3=1;
			OLED_P16x16Ch_2(48,4,16);
			OLED_P16x16Ch_2(64,4,17);
		}
		if(flag_ms==3) {
			LED2=0;
			LED3=0;
			OLED_P16x16Ch_2(48,4,18);
			OLED_P16x16Ch_2(64,4,19);
		}
		//第四行显示：速度
		OLED_P16x16Ch_2(0,6,12);
		OLED_P16x16Ch_2(16,6,13);
		OLED_ShowString(32,6,":",16);
		OLED_ShowNum(40,6,car_speed_level%10,1,16);
		OLED_P16x16Ch_2(0,6,12);
		OLED_P16x16Ch_2(16,6,13);
		OLED_ShowString(32,6,":",16);
		OLED_ShowNum(40,6,car_speed_level%10,1,16);
		OLED_P16x16Ch_2(64,6,20);
		OLED_P16x16Ch_2(80,6,21);
		OLED_ShowString(96,6,":",16);
		OLED_ShowNum(104,6,JL%1000,3,16);



		//控制执行
		if(flag_kg==1) {

			//自动避障模式
			if(flag_ms==1) {
				JL=(uint32_t) Hcsr04GetLength();
				if(JL>99) JL=99;
				JL=JL%100;
				//超声波避障模式
				if(JL<40) {
					SetMotorVoltageAndDirection(-sd_value,sd_value);
					delay_ms(500);
				} else {
					SetMotorVoltageAndDirection(sd_value,sd_value);
				}
			}
if(flag_ms==2)
{
    uint8_t L2 = CG_Z1;   // 最左
    uint8_t L1 = CG_Z2;   // 左
    uint8_t M  = CG_Z3;   // 中
    uint8_t R1 = CG_Y3;   // 右
    uint8_t R2 = CG_Y2;   // 最右

    // 记录上一次方向
    // 0=直行
    // 1=左
    // 2=右
    static uint8_t last_dir = 0;

    // ======================
    // 左直角弯 11100
    // ======================
    if(L2==1 && L1==1 && M==1 && R1==0 && R2==0)
    {
        // 左轮后退
        // 右轮前进
        SetMotorVoltageAndDirection(-760,860);

        last_dir = 1;

        // 锁定转向
        delay_ms(120);
    }

    // ======================
    // 右直角弯 00111
    // ======================
    else if(L2==0 && L1==0 && M==1 && R1==1 && R2==1)
    {
        SetMotorVoltageAndDirection(860,-760);

        last_dir = 2;

        delay_ms(120);
    }

    // ======================
    // 左锐角弯 10100
    // ======================
    else if(L2==1 && L1==0 && M==1 && R1==0 && R2==0)
    {
        // 甩头左转
        SetMotorVoltageAndDirection(-760,900);

        last_dir = 1;

        delay_ms(100);
    }

    // ======================
    // 右锐角弯 00101
    // ======================
    else if(L2==0 && L1==0 && M==1 && R1==0 && R2==1)
    {
        // 甩头右转
        SetMotorVoltageAndDirection(900,-760);

        last_dir = 2;

        delay_ms(100);
    }

    // ======================
    // 极限左偏 10000
    // ======================
    else if(L2==1 && L1==0 && M==0 && R1==0 && R2==0)
    {
        SetMotorVoltageAndDirection(-760,880);

        last_dir = 1;
    }

    // ======================
    // 极限右偏 00001
    // ======================
    else if(L2==0 && L1==0 && M==0 && R1==0 && R2==1)
    {
        SetMotorVoltageAndDirection(880,-760);

        last_dir = 2;
    }

    // ======================
    // 中等左偏 11000
    // ======================
    else if(L2==1 && L1==1)
    {
        SetMotorVoltageAndDirection(760,860);

        last_dir = 1;
    }

    // ======================
    // 中等右偏 00011
    // ======================
    else if(R1==1 && R2==1)
    {
        SetMotorVoltageAndDirection(860,760);

        last_dir = 2;
    }

    // ======================
    // 轻微左偏 01100
    // ======================
    else if(L1==1 && M==1)
    {
        // 左修正
        SetMotorVoltageAndDirection(760,820);

        last_dir = 1;
    }

    // ======================
    // 左偏 01000
    // ======================
    else if(L1==1)
    {
        SetMotorVoltageAndDirection(760,860);

        last_dir = 1;
    }

    // ======================
    // 轻微右偏 00110
    // ======================
    else if(R1==1 && M==1)
    {
        // 右修正
        SetMotorVoltageAndDirection(820,760);

        last_dir = 2;
    }

    // ======================
    // 右偏 00010
    // ======================
    else if(R1==1)
    {
        SetMotorVoltageAndDirection(860,760);

        last_dir = 2;
    }

    // ======================
    // 正中 00100
    // ======================
    else if(M==1 && L1==0 && R1==0)
    {
        // 左轮补偿
        SetMotorVoltageAndDirection(760,780);

        last_dir = 0;
    }

    // ======================
    // 全黑 十字 11111
    // ======================
    else if(L2==1 && L1==1 && M==1 && R1==1 && R2==1)
    {
        SetMotorVoltageAndDirection(760,780);

        last_dir = 0;
    }

    // ======================
    // 全白 丢线 00000
    // ======================
    else if(L2==0 && L1==0 && M==0 && R1==0 && R2==0)
    {
        // 按上一次方向找线

        if(last_dir == 1)
        {
            // 往左找线
            SetMotorVoltageAndDirection(-760,820);
        }
        else if(last_dir == 2)
        {
            // 往右找线
            SetMotorVoltageAndDirection(820,-760);
        }
        else
        {
            // 默认慢速前进
            SetMotorVoltageAndDirection(760,780);
        }
    }

    // ======================
    // 其它情况
    // ======================
    else
    {
        SetMotorVoltageAndDirection(760,780);
    }
}
			if(flag_ms==3) {
				// 前进
				if(car_zhiling==2) {
					SetMotorVoltageAndDirection(sd_value-20,sd_value);
				}

				// 后退
				else if(car_zhiling==8) {
					SetMotorVoltageAndDirection(-sd_value-20,-sd_value);
				}

				// 左转
				else if(car_zhiling==4) {
					// 左边停
					// 右边前进
					SetMotorVoltageAndDirection(0,sd_value);
				}

				// 右转
				else if(car_zhiling==6) {
					// 左边前进
					// 右边停
					SetMotorVoltageAndDirection(sd_value,0);
				}

				// 停止
				else if(car_zhiling==5) {
					SetMotorVoltageAndDirection(0,0);
				}
			}
		} else {
			SetMotorVoltageAndDirection(0,0);  // 关闭时立即停止电机
		}
	}
}
void RCC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//A3 A4 MOTORB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//B0 B1 MOTORA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//HC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //定时器时钟 pwm 控制电机

}
