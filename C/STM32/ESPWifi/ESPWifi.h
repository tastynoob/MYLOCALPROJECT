#ifndef ESPWIFI_H
#define ESPWIFI_H
#include "MYUSART.h"
#define wifi_tx tx2
#define wifi_rx rx2
extern byte wifi_Buffer[];




int WifiInit();

int ConnectWifi(char* wifi,char* password);
int ConnectTCP(char* ip,char* port);
int WifiSendString(char* str);







#endif