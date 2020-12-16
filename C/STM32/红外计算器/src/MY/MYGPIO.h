#ifndef MYGPIO_H
#define MYGPIO_H
//配置GPIO模式
#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "SysTick.h"
#include "stdio.h"

#define uchar unsigned char
#define byte unsigned char
#define ushort unsigned short
#define bool unsigned char
#define false 0
#define true !false

#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x02000000U + ((addr & 0xFFFFF) << 5U) + ((bitnum) << 2U))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
//IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 12)
#define GPIOB_ODR_Addr (GPIOB_BASE + 12)
#define GPIOC_ODR_Addr (GPIOC_BASE + 12)
#define GPIOD_ODR_Addr (GPIOD_BASE + 12)
#define GPIOE_ODR_Addr (GPIOE_BASE + 12)
#define GPIOF_ODR_Addr (GPIOF_BASE + 12)
#define GPIOG_ODR_Addr (GPIOG_BASE + 12)
#define GPIOA_IDR_Addr (GPIOA_BASE + 8)
#define GPIOB_IDR_Addr (GPIOB_BASE + 8)
#define GPIOC_IDR_Addr (GPIOC_BASE + 8)
#define GPIOD_IDR_Addr (GPIOD_BASE + 8)
#define GPIOE_IDR_Addr (GPIOE_BASE + 8)
#define GPIOF_IDR_Addr (GPIOF_BASE + 8)
#define GPIOG_IDR_Addr (GPIOG_BASE + 8)
//每个端口的输出输出
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) //输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  //输入
#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n)
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)
#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n)
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)
#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n)
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)
#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n)
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)
#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n)
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)
#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n)
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)

typedef enum
{
    PA,
    PB,
    PC,
    PD,
    PE,
    PF,
    PG,
} MYGPIO_TYPE;
typedef enum
{
    AIN = GPIO_Mode_AIN,
    IN_FLOATING = GPIO_Mode_IN_FLOATING,
    IPD = GPIO_Mode_IPD,
    IPU = GPIO_Mode_IPU,
    OUT_DD = GPIO_Mode_Out_OD,
    OUT_PP = GPIO_Mode_Out_PP, //推挽输出
    AF_OD = GPIO_Mode_AF_OD,
    AF_PP = GPIO_Mode_AF_PP,
} MYGPIO_Mode;
typedef enum
{
    _2MHz = GPIO_Speed_2MHz,
    _10MHz = GPIO_Speed_10MHz,
    _50MHz = GPIO_Speed_50MHz,
} MYGPIO_Speed;

#define Delayms(ms) SysTick_DelaySync(ms)
#define Delayus(us) SysTick_DelaySyncUs(us)

//引脚模式设置
void MYGPIO_ModeSet(MYGPIO_TYPE type, uint8_t pin, MYGPIO_Mode mode, MYGPIO_Speed speed);
//开启GPIO时钟
void MYGPIO_ClockOn(MYGPIO_TYPE type);




#endif