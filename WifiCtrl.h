#ifndef WiFiCtrl_H
#define WiFiCtrl_H
#define WIFI_AP_MODE 1
#define WIFI_STATION_MODE 0

extern bool bWifiMode;

void vidStartAcessPoint (void);
boolean bConnectWiFi (void);
void vidStartMDns(void);
#endif