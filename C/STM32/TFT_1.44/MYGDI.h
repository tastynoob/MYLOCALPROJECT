#ifndef MYGDI_H
#define MYGDI_H
#include "TFT.h"



typedef struct 
{
    //当前光标的高
    uchar th;
    //当前光标的宽
    uchar tw;
} Windows;
extern Windows win;


//绘制一个像素点
void MYGDI_DrawPixel(byte x, byte y,color col);
//绘制一个图片
void MYGDI_DrawRect(byte x, byte y, byte h, byte w, color col);

//绘制一个字符15*8
void MYGDI_DrawChar(char a);


#endif 