#ifndef TIMER_H
#define TIMER_H
//定时器和定时器中断


#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_it.h"

#define MYTIM_TIM_Cmd(TIMx, mode) TIM_Cmd(TIMx, mode)

//初始化定时器//arr自动重装溢出值，psc预分频
void MYTIM_Init(TIM_TypeDef *TIMx, u16 arr, u16 psc);
//设置定时器中断2-4,pre抢占式中断优先级，sub响应式中断优先级
void MYTIM_ITSetUP(u8 TimNO,int8_t pre,int8_t sub);

#endif