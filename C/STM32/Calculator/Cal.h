#ifndef CAL_H
#define CAL_H
#include <float.h>



typedef struct 
{
    char tag;
    float val;
} Token;


typedef struct 
{
    char* str;
    int p;
    Token buffer;
    char null;
} Parser;
//创建一个token
Token CreateToken(char ch);
Token CreateToken_(char ch,float v);

void Error();
void Push(Token* t);
//获取下一个Token
Token Get();
float Expression();
float Term();
float Primary();


float ParseGet(char* str);














#endif