/***********************************************************************************************************************************/
/*----------------------------------ESP8266 Wi-Fi & MQTT GPIO Control + Network Time Protocol ------------------------------------*/
/***********************************************************************************************************************************/
/*A local webserver is initiated after connecting to Wi-Fi.
   The webserver allows controlling the GPIO2 and setting a time
   to switch-on the GPIO2.
   The ESP8266 is also connected to Adafruit MQTT broker and publishes local sensor
   readings whenever the readings differ, to the topic "sensor".
   The ESP8266 is subscribed to a MQTT topic "OnOff" that controls the GPIO2 as well
*/
#include <Arduino.h>
/*-------------------Arduino Libraries-----------------*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <WifiCtrl.h>
#include <WebServ.h>
#include <MqttFunc.h>
#include <GetRESTful.h>
/*------------------------MQTT--------------------*/
#include <PubSubClient.h>
/*-----------------------------------------------------*/
#include "NTP.h"

#define interval  5000

unsigned int valueStr[5];
String OnOffStr = "ON" ;
bool OnOffStatus = 0;
/***********************************************************************************************************************************/
/*Additional boards manager URL:
  https://github.com/esp8266/Arduino/releases/download/2.3.0/package_esp8266com_index.json
*/
/*********************************************************************************************************************************/
#define bWIFI_CONNECTED 1
extern PubSubClient client;
extern WebServer server;
extern TimeCheck NonBlock20Sec;
extern TimeCheck NonBlock5Sec;
/*************************************************************************************************************************************************************/
/*------------------------------------------------------------------------ VOID SETUP ------------------------------------------------------------------------*/
/*************************************************************************************************************************************************************/
void setup(void)
{
  Serial.begin(9600); //setup Serial communication
  delay(500);
  /*************************************************************************************/
  /*---------------------------------- Coonect to Wifi ---------------------------------*/
  /**************************************************************************************/
  if ( bConnectWiFi() == bWIFI_CONNECTED )
  {
    bWifiMode = WIFI_STATION_MODE;
    vidNtpInit();
    vidMqttInit();
    vidStationWebServerInit();
    
  }
  /*************************************************************************************/
  /*------------------------------- Create Access Point -------------------------------*/
  /**************************************************************************************/
  else
  {
    bWifiMode = WIFI_AP_MODE;
    vidStartAcessPoint();
  }
  /*------------------------------------ Start HTML Web Server for UI ------------------------------------*/
  vidStartMDns();
}
  
/*************************************************************************************************************************************************************/
/*------------------------------------------------------------------------ VOID LOOP ------------------------------------------------------------------------*/
/*************************************************************************************************************************************************************/
void loop(void)
{
  //MDNS.update();
  /*During the loop, we constantly check if a new HTTP request is received by running server.handleClient .
    If handleClient detects new requests,
    it will automatically execute the right functions that we specified in the setup.*/
  server.handleClient();

  

  if (bWifiMode == WIFI_STATION_MODE)
  {
    vidMqttConnect();
    if (NonBlock20Sec.vidIsItTime())
    {
      NtpRequestTime();
      GetRestStart();
    }
  } 
  yield();
  
}


