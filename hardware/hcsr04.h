#ifndef __HCSR_H
#define __HCSR_H
#include "sys.h"

#define HCSR04_PORT     GPIOC
#define HCSR04_CLK      RCC_APB2Periph_GPIOC
#define HCSR04_TRIG     GPIO_Pin_14
#define HCSR04_ECHO     GPIO_Pin_15

#define TRIG_Send  PCout(14) 
#define ECHO_Reci  PCin(15)


void hcsr04_NVIC(void);
float Hcsr04GetLength(void );
void Hcsr04Init(void);

#endif

