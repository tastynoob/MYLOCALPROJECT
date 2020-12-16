
#include "TFT.h"
#include "MYGPIO.h"

//向SPI总线传输一个8位数据
void SPI_WriteData(byte Data)
{
    unsigned char i = 0;
    for (i = 8; i > 0; i--)
    {
        if (Data & 0x80)
            sda = 1; //输出数据
        else
            sda = 0;
        scl = 0;
        scl = 1;
        Data <<= 1;
    }
}
//向液晶屏写一个8位指令
void Lcd_WriteIndex(byte Data)
{
    cs = 0;
    rs = 0;
    SPI_WriteData(Data);
    cs = 1;
}
//向液晶屏写一个8位数据
void Lcd_WriteData(byte Data)
{

    cs = 0;
    rs = 1;
    SPI_WriteData(Data);
    cs = 1;
}
//向液晶屏写一个16位数据
void Lcd_WriteData_16(ushort Data)
{
    cs = 0;
    rs = 1;
    SPI_WriteData(Data >> 8); //写入高8位数据
    SPI_WriteData(Data);      //写入低8位数据
    cs = 1;
}
//LCD复位时序
void Reset(void)
{
    reset = 0;
    Delayms(100);
    reset = 1;
    Delayms(100);
}
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void TFT_Init(void)
{
    Reset(); //Reset before LCD Init.
    Lcd_WriteIndex(0x11); //Sleep exit
    Delayms(120);
    //ST7735R Frame Rate
    Lcd_WriteIndex(0xB1);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB2);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB3);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB4); //Column inversion
    Lcd_WriteData(0x07);

    //ST7735R Power Sequence
    Lcd_WriteIndex(0xC0);
    Lcd_WriteData(0xA2);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x84);
    Lcd_WriteIndex(0xC1);
    Lcd_WriteData(0xC5);

    Lcd_WriteIndex(0xC2);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0xC3);
    Lcd_WriteData(0x8A);
    Lcd_WriteData(0x2A);
    Lcd_WriteIndex(0xC4);
    Lcd_WriteData(0x8A);
    Lcd_WriteData(0xEE);

    Lcd_WriteIndex(0xC5); //VCOM
    Lcd_WriteData(0x0E);

    Lcd_WriteIndex(0x36); //MX, MY, RGB mode
    Lcd_WriteData(0xC8);

    //ST7735R Gamma Sequence
    Lcd_WriteIndex(0xe0);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x1a);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x18);
    Lcd_WriteData(0x2f);
    Lcd_WriteData(0x28);
    Lcd_WriteData(0x20);
    Lcd_WriteData(0x22);
    Lcd_WriteData(0x1f);
    Lcd_WriteData(0x1b);
    Lcd_WriteData(0x23);
    Lcd_WriteData(0x37);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0xe1);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x1b);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x17);
    Lcd_WriteData(0x33);
    Lcd_WriteData(0x2c);
    Lcd_WriteData(0x29);
    Lcd_WriteData(0x2e);
    Lcd_WriteData(0x30);
    Lcd_WriteData(0x30);
    Lcd_WriteData(0x39);
    Lcd_WriteData(0x3f);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00 + 2);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x80 + 2);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00 + 3);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x80 + 3);

    Lcd_WriteIndex(0xF0); //Enable test command
    Lcd_WriteData(0x01);
    Lcd_WriteIndex(0xF6); //Disable ram power save mode
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0x3A); //65k mode
    Lcd_WriteData(0x05);

    Lcd_WriteIndex(0x29); //Display on
}

/*************************************************
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void TFTSetRegion(byte x_start, byte y_start, byte x_end, byte y_end)
{
    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_start + 2);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_end + 2);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_start + 3);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_end + 3);

    Lcd_WriteIndex(0x2c);
}

//全屏填充函数
void TFTFillScreen(color col)
{
    uchar i, j;
    TFTSetRegion(0, 0, 128 - 1, 128 - 1);
    for (i = 0; i < 128; i++)
    {
        for (j = 0; j < 128; j++)
        {
            Lcd_WriteData_16(col);
        }
    }
}
