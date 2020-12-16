#include "Cal.h"
#include<stdio.h>
#include<math.h>

#include<string.h>
Parser parser = { 0,0,{0},1 };
int error_flag =0;
void Error(){
    error_flag = 1;
}

//创建一个token
Token CreateToken(char ch){
    Token t = {ch,0};
    return t;
}
Token CreateToken_(char ch,float v){
    Token t = {ch,v};
    return t;
}


void Push(Token* t){
    if(!parser.null){
        Error();
    }
    parser.buffer = *t;
    parser.null=0;
}
Token Get(){
    if(!parser.null){
        parser.null=1;
        return parser.buffer;
    }
    char ch = parser.str[parser.p++];
    float val;
    switch (ch)
    {
    case '=':
        return CreateToken(ch);
    case '+':case '-':case '*':case '/':case '(':case ')':
        return CreateToken(ch);
    case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9':
        parser.p--;
        sscanf(&parser.str[parser.p],"%f",&val);
        while((parser.str[parser.p]<='9' && parser.str[parser.p]>='0') || parser.str[parser.p]=='.')parser.p++;
        return CreateToken_('0',val);
    case 's':case 'c':case 't':
        return CreateToken(ch);
    default:
        return CreateToken(ch);
    }
}
float Expression(){
    float val = Term();
	Token t = Get();
	while (t.tag == '+' || t.tag == '-')
	{
		if (t.tag == '+')
		{
			val += Term();
			t = Get();
		}
		if (t.tag == '-')
		{
			val -= Term();
			t = Get();
		}
	}
	Push(&t);
	return val;
}
float Term(){
    float val = Primary();

	while (1)
	{
		Token token = Get();
		switch (token.tag)
		{
		case '*':
			val *= Primary();
			break;
		case '/':
			val /= Primary();
			break;
		default:
			Push(&token);
			return val;
		}
	}
}
float Primary() {
	float val=0;
	Token token = Get();


	switch (token.tag)
	{
	case '0':
		val = token.val;
		break;
	case '(':
		val = Expression();
		token = Get();
		if (token.tag != ')')
		{
			Error();
		}
		break;
	case 's':
		parser.p++;
		val = Expression();
		token = Get();
		if (token.tag != ')')
		{
			Error();
		}
		val = sin(val);
		break;
	case 'c':
		parser.p++;
		val = Expression();
		token = Get();
		if (token.tag != ')')
		{
			Error();
		}
		val = cos(val);
		break;
	case 't':
		parser.p++;
		val = Expression();
		token = Get();
		if (token.tag != ')')
		{
			Error();
		}
		val = tan(val);
		break;
	default:
		Error();
	}
	return val;
}



float ParseGet(char* str){
    parser.str = str;
	float val=0;
	while (1) {
		Token token = Get();
		if (token.tag == '=')
		{
            parser.null=1;
            parser.p=0;
            parser.str=0;
			return val;
		}
		else
		{
			Push(&token);
			val = Expression();
		}
		if (error_flag){
            error_flag = 0;

            parser.null=1;
            parser.p=0;
            parser.str=0;
            return FLT_MAX;
        }
	}
}