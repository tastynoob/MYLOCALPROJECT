#include "MYGDI.h"
#include "CHAR.h"

Windows win = {0,0};

//绘制一个像素点
void MYGDI_DrawPixel(byte x, byte y, color col){
    TFTSetRegion(x,y,x,y);
    TFTWriteColor(col);
}
//绘制一个矩形
void MYGDI_DrawRect(byte x, byte y, byte h, byte w, color col){
    TFTSetRegion(x,y,x+h,y+w);
    for(int i=0;i<h*w;i++)
    TFTWriteColor(col);
}


void MYGDI_DrawChar(char ch){  
    TFTSetRegion(win.tw,win.th,win.tw+7,win.th+15);
    char* a = CHAR_S;
    switch (ch)
    {
    case '0':
        a = CHAR_0;
        break;
    case '1':
        a = CHAR_1;
        break;
    case '2':
        a = CHAR_2;
        break;
    case '3':
        a = CHAR_3;
        break;
    case '4':
        a = CHAR_4;
        break;
    case '5':
        a = CHAR_5;
        break;
    case '6':
        a = CHAR_6;
        break;
    case '7':
        a = CHAR_7;
        break;
    case '8':
        a = CHAR_8;
        break;
    case '9':
        a = CHAR_9;
        break;
    case 'c':
        a = CHAR_C;
        break;
    case '.':
        a = CHAR_p;
        break;
    case 'i':
         a = CHAR_I;
        break;
    case 'o':
        a = CHAR_O;
        break;
    case '(':
        a = CHAR_L;
        break;
    case ')':
        a = CHAR_R;
        break;
    case 's':
        a = CHAR_S;
        break;
    case 'n':
        a = CHAR_N;
        break;
    case '+':
        a = CHAR_ADD;
        break;
    case '-':
        a = CHAR_SUB;
        break;
    case '*':
        a = CHAR_MUL;
        break;
    case '/':
        a = CHAR_DIV;
        break;
    case '=':
        a = CHAR_GET;
        break;
    }
    char k;
    for(int i=0;i<15;i++){
        for(int j=0;j<8;j++){
            k = a[i] & (1<<j);
            TFTWriteColor((k?RED:BLACK));
        }
    }

    win.tw+=7;
    if(win.tw>=120){
        win.th+=15;
        if(win.th>=120){
            TFTFillScreen(BLACK);
            win.th=0;
            win.tw=0;
        }
        win.tw=0;
    }
}