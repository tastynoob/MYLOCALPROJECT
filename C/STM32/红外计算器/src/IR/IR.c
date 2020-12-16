#include "IR.h"
#include "math.h"


int high_=0;//记录高电平的持续时间
int low_=0;//记录低电平的持续时间
int val[33];//31次结果


//获取红外一次脉冲的结果
//小于0为1，大于0为0
int IRWork(){
    low_=0;
    high_=0;
    while(IR==0 && low_<10000)low_++;
    while(IR==1 && high_<10000)high_++;
    return high_ - low_;
}
//获取红外一帧数据
uchar IRGet(){

    while(1){
        low_=0;
        high_=0;
        while(IR==1);
        while(IR==0 && low_<25000)low_++;
        while(IR==1 && high_<20000)high_++;
        if(low_ && high_){
            if((low_ > 10000&&low_ < 15000) && (high_ >10000 && high_ < 20000)){
                break; 
            }
        }
    }

    for(int i=0;i<33;i++){
        if(!(val[i] = IRWork())){
            return 255;
        }
    }

    if(val[32] < 6800) return 255;
    char result = 0;
    for(int i=0;i<8;i++){
        if((val[16 + i]>=0) == (val[24 + i]<0)){
            result += (val[16 + i]<0) * (int)pow(2,7-i);
        }
        else
        {
            return 255;
        }
    }
    switch (result)
    {
        case 151:
            return '1';
        case 103:
            return '2';
        case 79:
            return '3';
        case 207:
            return '4';
        case 231:
            return '5';
        case 133:
            return '6';
        case 239:
            return '7';
        case 199:
            return '8';
        case 165:
            return '9';
        case 189:
            return '0';
        case 173:
            return '=';
        case 31://t
            return '.';
        case 87:
            return '(';
        case 111:
            return ')';
        case 221:
            return '/';
        case 253:
            return 's';
        case 61:
            return 'c';
        case 93:
            return '+';
        case 157:
            return '-';
        case 29:
            return '*';
        default:
            return '*';
    }
    return 255;
}
