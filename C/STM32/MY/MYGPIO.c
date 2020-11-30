#include "MYGPIO.h"



void MYGPIO_SetGPMode(MYGPIO_TYPE type, MYGPIO_Mode mode, MYGPIO_Speed speed, uint8_t pin)
{
    GPIO_InitTypeDef GPIO_Def;
    GPIO_Def.GPIO_Pin = 1 << pin;
    GPIO_Def.GPIO_Mode = (GPIOMode_TypeDef)mode;
    GPIO_Def.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
    GPIO_Init((GPIO_TypeDef *)((uint32_t)(0x40010800 + type * 0x0400)), &GPIO_Def);
}

//开启GPIO时钟
void MYGPIO_SetClockOn(MYGPIO_TYPE type)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA + type * 0x00000004, ENABLE);
}
