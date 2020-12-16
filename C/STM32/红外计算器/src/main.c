#include "MYGPIO.h"
#include "MYUSART.h"
#include "IR.h"
#include "string.h"
#include "Cal.h"
#include "MYGDI.h"


void Init(){
    //SysTick_Init(72);
    MYGPIO_ClockOn(PB);
    MYGPIO_ModeSet(PB,1,IN_FLOATING,_50MHz);
    MYUSART_Config(USART1);
    MYUSART_Init(USART1,115200);


    MYGPIO_ModeSet(PB,12,OUT_PP,_50MHz);
    MYGPIO_ModeSet(PB,13,OUT_PP,_50MHz);
    MYGPIO_ModeSet(PB,14,OUT_PP,_50MHz);
    MYGPIO_ModeSet(PB,15,OUT_PP,_50MHz);
    MYGPIO_ModeSet(PA,8,OUT_PP,_50MHz);

    TFT_Init();
    TFTFillScreen(BLACK);
}
char res[20];
char str[100] ={0};
int i=0;
char flag = 0;
int main()
{
    Init();
    uchar h=0;
    while(1){
        while((h=IRGet()) > 127);//接受一个字符
        if(flag){
            flag = 0;
            win.th=0;
            win.tw=0;
            TFTFillScreen(BLACK);
        }
        str[i++]=h;
        printf("%d\n",h);

        if(h=='s'){
            MYGDI_DrawChar('s');
            MYGDI_DrawChar('i');
            MYGDI_DrawChar('n');
        }
        else if(h=='c'){
            MYGDI_DrawChar('c');
            MYGDI_DrawChar('o');
            MYGDI_DrawChar('s');
        }
        else
        {
            MYGDI_DrawChar(h);
        }



        if(h=='='){
            flag = 1;
            str[i]=0;
            i=0;
            float val = ParseGet(str);
            if(val == FLT_MAX){
                MYGDI_DrawChar('*');
                MYGDI_DrawChar('*');
                MYGDI_DrawChar('*');
            }
            else
            {
                sprintf(res,"%f",val);
                for(int i=0;i<strlen(res);i++){
                    MYGDI_DrawChar(res[i]);
                }
            }
        }




    }
}


