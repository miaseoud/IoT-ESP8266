#include "mainHTML.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <MqttFunc.h>
/*------------------------MQTT--------------------*/
#include <PubSubClient.h>
/*-----------------------------------------------------*/
#include "NTP.h"
#include "WebServ.h"
extern WebServer server;
extern PubSubClient client;
extern int alarmmins;

void handleStation() {
server.send(200, "text/html", form);
}

void handleAP() {
server.send(200, "text/html", formAP);
}
  /*************************************************************************************/
  /*---------------------------------- Called on "ON" ---------------------------------*/
  /**************************************************************************************/
void handleOn() {

  server.send(200, "text/html", form);
    Serial.print("Publish Status:");
    Serial.println (client.publish(USERNAME PREAMBLE ON_OFF_TOPIC, "ON"));
    digitalWrite(23, LOW);

}
  /*************************************************************************************/
  /*---------------------------------- Called on "OFF"  ---------------------------------*/
  /**************************************************************************************/
void handleOff() {

  server.send(200, "text/html", form);
      Serial.print("Publish Status:");
    Serial.println (client.publish(USERNAME PREAMBLE ON_OFF_TOPIC, "OFF"));
    digitalWrite(23, HIGH);
}
 /*************************************************************************************/
 /*----------------------------- Called on "Cancel Alarm"  ----------------------------*/
 /**************************************************************************************/
void handleCancel() {
  alarmmins = 1000000;
  Serial.println ("Alarm Cancelled");
  server.send(200, "text/html", form);
}
  /*************************************************************************************/
  /*---------------------------------- Called on "Set Alarm" ---------------------------*/
  /**************************************************************************************/
void handleAlarm() {
  server.send(200, "text/html", form);
  int alarhour  = server.arg("alarmHour").toInt();
  int alarmint  = server.arg("alarmMint").toInt();
  Serial.print("Alarm Set for ");
  Serial.print(alarhour);
  Serial.print(":");
  Serial.print(alarmint);
  Serial.println ();
  alarmmins = alarhour* 60 + alarmint;
}


void handlePOT()
{
  static unsigned char u8testCount = 0;
  u8testCount++;
 String POTval = String(u8testCount);
 server.send(200, "text/plane", POTval);
}