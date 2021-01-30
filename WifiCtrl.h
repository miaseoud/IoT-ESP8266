#ifndef WiFiCtrl_H
#define WiFiCtrl_H

#include <Arduino.h>

enum wirelessState {stateConnect,stateStation,stateAccessPoint};

extern enum wirelessState wifiState;
extern bool bWifiMode;

extern const char *ssidap;
extern const char *passwordap;


void vidStartAcessPoint (void);
boolean bConnectWiFi (void);
void vidStartMDns(void);
#endif