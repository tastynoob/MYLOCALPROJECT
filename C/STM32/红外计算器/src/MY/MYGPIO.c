#include "MYGPIO.h"



void MYGPIO_ModeSet(MYGPIO_TYPE type, uint8_t pin, MYGPIO_Mode mode, MYGPIO_Speed speed)
{
    GPIO_InitTypeDef GPIO_Def;
    GPIO_Def.GPIO_Pin = 1 << pin;
    GPIO_Def.GPIO_Mode = (GPIOMode_TypeDef)mode;
    GPIO_Def.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
    if(type == PA)
    GPIO_Init(GPIOA, &GPIO_Def);
    if(type == PB)
    GPIO_Init(GPIOB, &GPIO_Def);
    if(type == PC)
    GPIO_Init(GPIOC, &GPIO_Def);
    if(type == PD)
    GPIO_Init(GPIOD, &GPIO_Def);
    if(type == PE)
    GPIO_Init(GPIOE, &GPIO_Def);
    
}

//开启GPIO时钟
void MYGPIO_ClockOn(MYGPIO_TYPE type)
{
    if(type == PA)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    if(type == PB)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    if(type == PC)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    if(type == PD)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
}
