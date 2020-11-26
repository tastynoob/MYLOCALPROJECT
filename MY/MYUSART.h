#ifndef MYUSART_H
#define MYUSART_H
//串口通信


#include "MYGPIO.h"
#include "stm32f10x_usart.h"
#include "stdio.h"



//判断接受寄存器是否有数据
#define Available(USARTx) (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == SET)


//配置串口的gpio以及时钟
void MYUSART_Config(USART_TypeDef* USARTx);
//设置串口波特率
void MYUSART_Init(USART_TypeDef* USARTx,int baudRate);
//串口发送数据
bool SendByte(USART_TypeDef *USARTx, byte data);
//阻塞式串口接收数据
byte ReceiveByte(USART_TypeDef* USARTx);
//发送字符串
void SendString(USART_TypeDef* USARTx,byte* str);
//阻塞式接受字符串,返回接受的字符串长度
int ReceiveString(USART_TypeDef*USARTx,byte* buffer);





#endif