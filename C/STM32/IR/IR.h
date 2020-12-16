#ifndef IR_H
#define IR_H
#include "MYGPIO.h"
#include "MYIT.h"
#include "MYUSART.h"


//输出
#define IR PBin(1)



//获取红外一帧数据
uchar IRGet();




#endif