#ifndef OLED_H_INCLUDED
#define OLED_H_INCLUDED

#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"

#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//-----------------OLED端口定义----------------
//SCL          PC0
//SDA          PC1 		     
						 
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_12);//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_12);

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_15);//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_15);


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据




//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p,uint8_t Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);

void IIC_Wait_Ack(void);
void OLED_MakePoint(unsigned char x,unsigned char y,unsigned char p);
void OLED_P16x16Ch_2(u8 x, u8 y, u8 N);

////OLED控制用函?
//void OLED_Display_Off(void);
//void OLED_WR_Byte(unsigned dat,unsigned cmd);
//void delay_us(uint32_t value);
//void SDA_OUT(void);
//void SDA_IN(void);
//void IIC_Start(void);
//void IIC_Stop(void);
//uint8_t IIC_Wait_Ask(void);
//void IIC_WriteByte(uint8_t data);
//uint8_t IIC_ReadByte(void);
//void WriteCmd(uint8_t command);
//void WriteDat(uint8_t data);
//void OLED_Init(void);
//void OLED_ON(void);
//void OLED_SetPos(unsigned char x, unsigned char y) ;//???????
//void OLED_fill(unsigned char fill_Data);//????
//void OLED_CLS(void);//??
//void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);





#endif // OLED_H_INCLUDED
