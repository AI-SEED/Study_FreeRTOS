#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"




//通过改变TIM14->CCR1的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL TIM14->CCR1    
extern volatile unsigned long long FreeRTOSRunTimeTicks;
void ConfigureTimeForRunTimeStats(void);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM14_PWM_Init(u32 arr,u32 psc);
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);
#endif























