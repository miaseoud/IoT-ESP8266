#include "mainHTML.h"
  
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <handleFunctions.h>
const int led = 23;
WebServer server(80);
void vidStationWebServerInit (void)
{

pinMode(led, OUTPUT); 
server.on("/",    handleStation);
server.on("/ON",    handleOn);
server.on("/OFF",   handleOff);
server.on("/alarm", handleAlarm);
server.on("/cancel", handleCancel);
server.on("/readPOT", handlePOT);
/*start listening for HTTP requests*/
server.begin();
Serial.println("HTTP webserver started");

}

void vidApWebServerInit (void)
{

pinMode(led, OUTPUT); 
server.on("/",    handleAP);
server.on("/AP",    handleOn);
/*start listening for HTTP requests*/
server.begin();
Serial.println("HTTP webserver started");

}


String form = R"***(
             <!DOCTYPE html>
            <HEAD>
              <TITLE>Basic HTML Sample Page</TITLE>
              <style>
              body
              {
               background: rgb(2,0,36);
               background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(68,116,126,0.12088585434173671) 32%);
              }
              </style>
              </HEAD>
              <html>
              <CENTER>
              //<BODY BGCOLOR=Yellow>
              <br><br><br><br>
              <H1>Wi-Fi Controller</H1>
              <IMG SRC='https://www.shareicon.net/data/256x256/2017/06/23/887677_internet_512x512.png'>
              <form action='/ON'><input type='submit' value='Turn On'></form>
              <form action='/OFF'><input type='submit' value='Turn Off'></form>
              <h3> Counter : <span style='color:yellow' id='POTvalue'>0</span></h3>
              <form action='/alarm'><p>Alarm <input type='text' name='alarmHour' size=1>:<input type='text' name='alarmMint' size=1><input type='submit' value='Set'></form>
              <form action='/cancel'><input type='submit' value='Cancel Alarm'></form>
              </CENTER>
              <center>
              <br>
              <H5>Copyright 2020, by <A HREF='test'>Mahmoud Aboul-Seoud</A></H5>


            <script>
            setInterval(function()
            {
            getPOTval();
            }, 2000);
            //-------------------------------------------------------
            function getPOTval()
             {
             var POTvalRequest = new XMLHttpRequest();
             POTvalRequest.onreadystatechange = function()
            {
              if(this.readyState == 4 && this.status == 200)
              {
            document.getElementById("POTvalue").innerHTML =
            this.responseText;
              }
             };
            POTvalRequest.open("GET", "readPOT", true);
            POTvalRequest.send();
            }
            </script>
            </html>
            )***"

              ;



String formAP = R"***(
             <!DOCTYPE html>
            <HEAD>
              <TITLE>Basic HTML Sample Page</TITLE>
              <style>
              body
              {
               background: rgb(2,0,36);
               background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(68,116,126,0.12088585434173671) 32%);
              }
              </style>
              </HEAD>
              <html>
              <CENTER>
              //<BODY BGCOLOR=Yellow>
              <br><br><br><br>
              <H1>Wi-Fi Controller AP</H1>
              <IMG SRC='https://www.shareicon.net/data/256x256/2017/06/23/887677_internet_512x512.png'>
              <form action='/ON'><input type='submit' value='Turn On'></form>
              <form action='/OFF'><input type='submit' value='Turn Off'></form>
              <h3> Counter : <span style='color:yellow' id='POTvalue'>0</span></h3>
              <form action='/alarm'><p>Alarm <input type='text' name='alarmHour' size=1>:<input type='text' name='alarmMint' size=1><input type='submit' value='Set'></form>
              <form action='/cancel'><input type='submit' value='Cancel Alarm'></form>
              </CENTER>
              <center>
              <br>
              <H5>Copyright 2020, by <A HREF='test'>Mahmoud Aboul-Seoud</A></H5>


            <script>
            setInterval(function()
            {
            getPOTval();
            }, 2000);
            //-------------------------------------------------------
            function getPOTval()
             {
             var POTvalRequest = new XMLHttpRequest();
             POTvalRequest.onreadystatechange = function()
            {
              if(this.readyState == 4 && this.status == 200)
              {
            document.getElementById("POTvalue").innerHTML =
            this.responseText;
              }
             };
            POTvalRequest.open("GET", "readPOT", true);
            POTvalRequest.send();
            }
            </script>
            </html>
            )***"

              ;