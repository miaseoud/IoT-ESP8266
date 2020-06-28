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
/*-------------------Arduino Libraries-----------------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
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
extern ESP8266WebServer server;
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
    vidNtpInit();
    vidMqttInit();
  }
  /*************************************************************************************/
  /*------------------------------- Create Access Point -------------------------------*/
  /**************************************************************************************/
  else
  {
    vidStartAcessPoint();
  }
  /*------------------------------------ Start HTML Web Server for UI ------------------------------------*/
  vidStartMDns();
  vidWebServerInit();
}
/*************************************************************************************************************************************************************/
/*------------------------------------------------------------------------ VOID LOOP ------------------------------------------------------------------------*/
/*************************************************************************************************************************************************************/
void loop(void)
{
  yield();
  /*During the loop, we constantly check if a new HTTP request is received by running server.handleClient .
    If handleClient detects new requests,
    it will automatically execute the right functions that we specified in the setup.*/
  server.handleClient();

  vidMqttConnect();

  if (NonBlock20Sec.vidIsItTime())
  {
    NtpRequestTime();
    GetRestStart();
  }

  MDNS.update();
}


