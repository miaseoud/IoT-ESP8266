#ifndef MAINHTML_H
#define MAINHTML_H

#include <WiFi.h>

//html page
bool bConnectWiFi (void);
void vidNtpInit (void);
void vidStartAcessPoint (void);
void vidStationWebServerInit (void);
void vidMqttInit (void);
int NtpRequestTime (void);
void vidMqttReconnect(void);
void callback(char* topic, unsigned char * data, unsigned int length);
unsigned long sendNTPpacket(IPAddress& address);
extern String form;
extern String formAP;

#endif
