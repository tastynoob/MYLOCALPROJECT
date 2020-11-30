#include "SysTick.h"
#include "MYGPIO.h"
#include "MYTIMER.h"
#include "TFT.h"
#include "MYUSART.h"
#include "MYGDI.h"
#include "stdlib.h"

#define up PBin(12)
#define down PBin(13)
#define left PBin(14)
#define right PBin(15)

int _kbhit()
{
    return Available(USART1);
}
int _getch()
{
    SendByte(USART1, '!');
    return ReceiveByte(USART1);
}
int th = 0, tw = 0;
color col = WHITE;

void _cputs()
{
    MYGDI_DrawRect(tw, th, 8, 8, col);
    tw += 7;
    if (tw > 7 * 15)
    {
        tw = 0;
        th += 7;
    }
}
int Jump()
{
    th += 7;
    tw = 0;
    return 1;
}
void Delay(int n)
{
    int k = n;
    int a = 100;
    while (k--)
        while (a--)
            ;
}

void Snaker()
{
    int w = 15, s = w * w, *m, z[2] = {0}, l = 3, c = 'D', C, i, f, *p;
    int M[15 * 15] = {0};
    m = M;

    for (srand((int)m), C = m[1] = -1; C - 27;)
    {
        if (_kbhit())
            C = _getch() & 95, C - 65 && C - 68 && C - 83 && C - 87 || (c ^ C) & 20 ^ 4 && (c = C);
        p = z + !!(c & 2), *p += c / 3 & 2, *p = (--*p + w) % w;

        f = 1, *(p = m + *z + z[1] * w) > 0 && (C = 27);

        for (; *p && (m[i = rand() % s] || (--m[i], ++l, --f));)
            ;

        tw = 0;
        th = 0;

        for (i = 0, *p = l; i < s; _cputs(), ++i % w || Jump())
            col = (m[i] > 0 ? m[i] -= f, 192 : m[i] ? 160 : 240) + 250;
    }
}
