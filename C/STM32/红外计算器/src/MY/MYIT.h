#ifndef MYIT_H
#define MYIT_H 
#include "MYGPIO.h"
#include "stm32f10x_exti.h"




void GPIO_ITSet(MYGPIO_TYPE Px,int8_t pin,int pre,int sub);




void EXTI0_IRQHandler();
void EXTI1_IRQHandler();
void EXTI2_IRQHandler();
void EXTI3_IRQHandler();
void EXTI4_IRQHandler();
void EXTI9_5_IRQHandler();
void EXTI15_10_IRQHandler();




#endif