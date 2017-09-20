/***********************************************************************************************************************************/
/*----------------------------------ESP8266 Wi-Fi & MQTT GPIO Control + Network Time Protocol ------------------------------------*/
/***********************************************************************************************************************************/
/*A local webserver is initiated after connecting to Wi-Fi. 
 * The webserver allows controlling the GPIO2 and setting a time
 * to switch-on the GPIO2.
 * The ESP8266 is also connected to Adafruit MQTT broker and publishes local sensor
 * readings whenever the readings differ, to the topic "sensor".
 * The ESP8266 is subscribed to a MQTT topic "OnOff" that controls the GPIO2 as well
 */
/*-------------------Arduino Libraries-----------------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
/*-----------------------------------------------------*/
#include "NTP.h"
#include "mainHTML.h"
/*------------------------MQTT--------------------*/
#include <PubSubClient.h>
/*--------Connect-------*/
#define SERVER          "io.adafruit.com"
#define SERVERPORT      1883
#define MQTT_USERNAME   "m....."
#define MQTT_KEY        "fbe168e8eca242d38eecf12d49db6f92"
/*--------Publish-------*/
#define USERNAME          "m...../"
#define PREAMBLE          "Feeds/"
#define TOPIC             "sensor"
/*--------Subscribe-------*/
#define T_COMMAND         "OnOff"

float sensorValue, prevsensorValue = -1;
char valueStr[5];

WiFiClient WiFiClient;
// create MQTT object
PubSubClient client(WiFiClient);

/***********************************************************************************************************************************/
/*Additional boards manager URL:
  https://github.com/esp8266/Arduino/releases/download/2.3.0/package_esp8266com_index.json
*/
/***********************************************************************************************************************************/
/*-------------------------------------------------------WiFi SSID & Password----------------------------------------------------*/
/***********************************************************************************************************************************/
char ssid[] = "Ray-Ban 2";           //   network SSID
char pass[] = "Mido&Nody@15";        //   network passord
/***********************************************************************************************************************************/
/*-------------------------------------------------------Access Point Settings----------------------------------------------------*/
/***********************************************************************************************************************************/
const char *ssidap = "ESP AP";
const char *passwordap = "anypassword";
IPAddress  apIP (192, 168, 0, 200);
/*******************************************************************************************************************************/
#define interval  50000
long previousMillis = 0;
int alarmmins = 1000000;
int mins;
/*********************************************************************************************************************************/
ESP8266WebServer server(80);
#define  led 2
/*************************************************************************************************************************************************************/
/*------------------------------------------------------------------------ VOID SETUP ------------------------------------------------------------------------*/
/*************************************************************************************************************************************************************/
void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(9600); //setup Serial communication
  delay(500);
  /*************************************************************************************/
  /*---------------------------------- Coonect to Wifi ---------------------------------*/
  /**************************************************************************************/
  //WiFi.mode(WIFI_STA);
  //WiFi.config(IPAddress(192,168,1,100),  IPAddress(255,25,255,0) , IPAddress(192,168,1,1));
  Serial.println(" ");
  Serial.print("Connecting ");

  /* ---- Wait for connection to establish ----*/
  for (int tries = 0; (WiFi.status() != WL_CONNECTED) && tries < 10; tries++) {
    delay(500);
    Serial.print(". ");
  }
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());

    client.setServer(SERVER, SERVERPORT);// MQTT broker address and port numnber
    client.setCallback(callback);
  }
  /*************************************************************************************/
  /*------------------------------- Create Access Point -------------------------------*/
  /**************************************************************************************/
  else {
    delay(1000);
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssidap, passwordap);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("");
    Serial.println("Not connected to WiFI");
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }
    pinMode(A0, INPUT);
  /*------------------------------------Server ON------------------------------------*/
  server.on("/", []() {
    server.send(200, "text/html", form);
  });
  server.on("/ON",    handleOn);
  server.on("/OFF",   handleOff);
  server.on("/alarm", handleAlarm);
  server.on("/cancel", handleCancel);

  server.begin();
  Serial.println("HTTP server started");
}
/*************************************************************************************************************************************************************/
/*------------------------------------------------------------------------ VOID LOOP ------------------------------------------------------------------------*/
/*************************************************************************************************************************************************************/
void loop(void) {
  server.handleClient();
  /***********************************************************************************************************************/
  /*------------------------------------------------------- Check Time ------------------------------------------------*/
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) > interval) { //In order to not use request NTP continuisly
    previousMillis = currentMillis;
    mins = requestTime();
    /*------------------------------------ Check ALARM ----------------------------------------------*/
    if (mins >= alarmmins) { //mins=minutes from 0:00 to current time
      Serial.println("Activate Alarm");//Alert set time is now
      digitalWrite (led, 1);
    }
  }
/*--------Connect-------*/
  yield();
  if (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Connect to MQTT broker
    if (client.connect("", MQTT_USERNAME, MQTT_KEY)) {
      Serial.println("Connected to MQTT broker");
/*--------Subscribe-------*/
      client.subscribe(USERNAME PREAMBLE T_COMMAND, 1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
/**********************************************************************************************/
/*--------Publish-------*/
  sensorValue = analogRead (A0);
  if (client.connected() && prevsensorValue != sensorValue) {
    String str = (String)sensorValue;
    str .toCharArray(valueStr, 5);
    client.publish(USERNAME PREAMBLE TOPIC, valueStr);
    Serial.println("Publish Sensor Value");
    prevsensorValue = sensorValue;
    delay(500);
  }
  client.loop();
/**********************************************************************************************/
}
/*--------Subscribe Action-------*/
void callback(char* topic, byte * data, unsigned int length) {
  // handle message arrived {
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)data[i]);
  }
  Serial.println();
  if (data[1] == 'F')  {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
}
/*config.IP[0] = 192;config.IP[1] = 168;config.IP[2] = 1;config.IP[3] = 100;
  config.Netmask[0] = 255;config.Netmask[1] = 255;config.Netmask[2] = 255;config.Netmask[3] = 0;
  config.Gateway[0] = 192;config.Gateway[1] = 168;config.Gateway[2] = 1;config.Gateway[3] = 1;
  WiFi.config(IPAddress(config.IP[0],config.IP[1],config.IP[2],config.IP[3] ),  IPAddress(config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3] ) , IPAddress(config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3] ));
*/

