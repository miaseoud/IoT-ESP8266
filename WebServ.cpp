#include "mainHTML.h"
  
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <handleFunctions.h>
const int led = 23;
WebServer server(80);
void vidWebServerInit (void)
{

pinMode(led, OUTPUT); 
server.on("/",    handle);
server.on("/ON",    handleOn);
server.on("/OFF",   handleOff);
server.on("/alarm", handleAlarm);
server.on("/cancel", handleCancel);
/*start listening for HTTP requests*/
server.begin();
Serial.println("HTTP webserver started");

}


String form = "<HEAD>"
              "<TITLE>Basic HTML Sample Page</TITLE>"
              "<style>"
              "body"
              "{"
               "background: rgb(2,0,36);"
               "background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(68,116,126,0.12088585434173671) 32%);"
              "}"
              "</style>"
              "</HEAD>"
              "<CENTER>"
              //"<BODY BGCOLOR=Yellow>"
              "<br><br><br><br>"
              "<H1>Wi-Fi Controller</H1>"
              "<IMG SRC='https://www.shareicon.net/data/256x256/2017/06/23/887677_internet_512x512.png'>"
              "<form action='/ON'><input type='submit' value='Turn On'></form>"
              "<form action='/OFF'><input type='submit' value='Turn Off'></form>"
              "<form action='/alarm'><p>Alarm <input type='text' name='alarmHour' size=1>:<input type='text' name='alarmMint' size=1><input type='submit' value='Set'></form>"
              "<form action='/cancel'><input type='submit' value='Cancel Alarm'></form>"
              "</CENTER>"
              "<center>"
              "<br>"
              "<H5>Copyright 2020, by <A HREF='test'>Mahmoud Aboul-Seoud</A></H5>"
              ;