#include "MYTIMER.h"
#include "MYGPIO.h"

void MYTIM_Init(TIM_TypeDef *TIMx, uint16_t arr, uint16_t psc)
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
}

void MYTIM_ITSetUP(TIM_TypeDef *TIMx, int8_t pre, int8_t sub)
{
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_Def;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置中断分组
    switch ((int)TIMx)
    {
    case (int)TIM2:
        NVIC_Def.NVIC_IRQChannel = TIM2_IRQn;
        break;
    case (int)TIM3:
        NVIC_Def.NVIC_IRQChannel = TIM3_IRQn;
        break;
    case (int)TIM4:
        NVIC_Def.NVIC_IRQChannel = TIM4_IRQn;
        break;
    case (int)TIM5:
        break;
    }
    NVIC_Def.NVIC_IRQChannelPreemptionPriority = pre; //抢占式中断优先级设为0
    NVIC_Def.NVIC_IRQChannelSubPriority = sub;        //响应式中断优先级设为0
    NVIC_Def.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Def);
    TIM_Cmd(TIMx, ENABLE);
}

void MYPWM_Init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                        //定义结构体
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //使能GPIO外设和AFIO复用功能模块时钟
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);                        //选择Timer3部分重映像
    //选择定时器3的通道2作为PWM的输出引脚TIM3_CH2->PB5    GPIOB.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化引脚

    MYTIM_Init(TIM3, arr, psc);

    TIM_OCInitTypeDef TIM_OCInitStructure;                        //定义结构体
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //选择定时器模式，TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;      //输出比较极性低
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                      //根据结构体信息进行初始化
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);             //使能定时器TIM2在CCR2上的预装载值

    TIM_Cmd(TIM3, ENABLE); //使能定时器TIM3
}
