#include "MYTIMER.h"



void MYTIM_Init(TIM_TypeDef *TIMx, u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_Def;
    if (TIMx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if (TIMx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if (TIMx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    else if (TIMx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    TIM_DeInit(TIMx);
    //TIM_InternalClockConfig(TIMx);

    TIM_Def.TIM_Period = arr - 1;    //自动重装载值
    TIM_Def.TIM_Prescaler = psc - 1; //预分频
    //TIM_Def.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割

    TIM_Def.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInit(TIMx, &TIM_Def);
    //TIM_ARRPreloadConfig(TIMx, DISABLE);

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}

void MYTIM_ITSetUP(u8 TimNO,int8_t pre,int8_t sub)
{
    NVIC_InitTypeDef NVIC_Def;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置中断分组
    switch (TimNO)
    {
    case 2:
        NVIC_Def.NVIC_IRQChannel = TIM2_IRQn;
        break;
    case 3:
        NVIC_Def.NVIC_IRQChannel = TIM3_IRQn;
        break;
    case 4:
        NVIC_Def.NVIC_IRQChannel = TIM4_IRQn;
        break;
    case 5:

        break;
    }
    NVIC_Def.NVIC_IRQChannelPreemptionPriority = pre; //抢占式中断优先级设为0
    NVIC_Def.NVIC_IRQChannelSubPriority = sub;        //响应式中断优先级设为0
    NVIC_Def.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Def);
}
