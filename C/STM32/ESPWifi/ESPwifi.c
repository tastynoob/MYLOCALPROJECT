#include "ESPWifi.h"
#include "string.h"
byte wifi_Buffer[200];


int WifiInit(){
    MYUSART_Config(USART2);
    MYUSART_Init(USART2,115200);
    SendString(USART2,"AT\n");
    int timeout = 10000;
    while(!Available(USART2)){
        timeout--;
        if(timeout<0){
            return 0;
        }
    }
    WReceiveString(USART2,wifi_Buffer);
    return 1;
}


int ConnectWifi(char* wifi,char* password){
    UsartGetByte(USART2);
    SendString(USART2,"AT+CWJAP=\"");
    SendString(USART2,wifi);
    SendString(USART2,"\",\"");
    SendString(USART2,password);
    SendString(USART2,"\"\r\n");
    WReceiveString(USART2,wifi_Buffer);
    return 0;
}

int ConnectTCP(char* ip,char* port){
    UsartGetByte(USART2);
    SendString(USART2,"AT+CIPSTART=\"TCP\",\"");
    SendString(USART2,ip);
    SendString(USART2,"\",");
    SendString(USART2,port);
    SendString(USART2,"\r\n");
    WReceiveString(USART2,wifi_Buffer);
    return 0;
}

int WifiSendString(char* str){
    SendString(USART2,"AT+CIPSEND=");
    SendByte(USART2,strlen(str) + '0');
    SendString(USART2,"\r\n");
    Delayms(1);
    return 1;
}