#ifndef TFT_H
#define TFT_H

#define color unsigned short


#include "MYGPIO.h"
//#define bl PBout(11)    //BL
#define rs PBout(12)    //D/C
#define reset PBout(13) //RST
#define cs PBout(14)    //CS
#define scl PBout(15)   //CLK
#define sda PAout(8)   //DIN


//单片机IO推挽输出设置定义

//定义常用颜色
#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xEF7D
#define GRAY1 0x8410
#define GRAY2 0x4208

#define TFTWriteColor(color) Lcd_WriteData_16(color)


void SPI_WriteData(byte Data);
void Lcd_WriteIndex(byte Data);
void Lcd_WriteData(byte Data);
void Lcd_WriteData_16(ushort Data);
void Reset(void);
void TFT_Init(void);
void TFTSetRegion(byte x_start, byte y_start, byte x_end, byte y_end);
void TFTFillScreen(color col);

#endif