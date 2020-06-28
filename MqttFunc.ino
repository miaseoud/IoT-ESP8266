
#include <PubSubClient.h>
/*--------Connect-------*/
#define SERVER          "io.adafruit.com"
#define SERVERPORT      1883
#define MQTT_USERNAME   "miaseoud"
#define MQTT_KEY        ""


WiFiClient WiFi_Client;//Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().
//Creates an uninitialised client instance(MQTT object).
//Before it can be used, it must be configured with the property setters:
PubSubClient client(WiFi_Client);//Constructor


/**********************************************************************************************/
/*--------Subscribe Action-------*/
void callback(char* topic, byte * data, unsigned int length)
{
  /*topic - the topic the message arrived on (const char[])
    payload - the message payload (byte array)
    length - the length of the message payload (unsigned int)*/
  Serial.print("OnOff status is: ");
  if (data[1] == 'F')
  {
    OnOffStatus = 0;
    Serial.print("Off");
    // digitalWrite(LEDBLUE, LOW);
  }
  else if (data[1] == 'N')
  {
    OnOffStatus = 1;
    Serial.print("On");
    // digitalWrite(LEDBLUE, HIGH);
  }
  else
  {
    Serial.print("Unexpected");
  }
  Serial.println();
}


void vidMqttReconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("MqttClient", MQTT_USERNAME, MQTT_KEY))  //connect (clientID, username, password)
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 10 seconds");
      // Wait 5 seconds before retrying
      delay(10000);
    }
  }
}


void vidMqttInit (void)
{
  client.setServer(SERVER, SERVERPORT);
  client.subscribe(USERNAME PREAMBLE ON_OFF_TOPIC, 1);
  client.setCallback(callback);
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT . . .");
    if (client.connect("MqttClient", MQTT_USERNAME, MQTT_KEY))  //connect (clientID, username, password)
    {
      Serial.println("Connected to MQTT server");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
/*
  -4 : MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time
  -3 : MQTT_CONNECTION_LOST - the network connection was broken
  -2 : MQTT_CONNECT_FAILED - the network connection failed
  -1 : MQTT_DISCONNECTED - the client is disconnected cleanly
   0 : MQTT_CONNECTED - the cient is connected
   1 : MQTT_CONNECT_BAD_PROTOCOL - the server doesn't support the requested version of MQTT
   2 : MQTT_CONNECT_BAD_CLIENT_ID - the server rejected the client identifier
   3 : MQTT_CONNECT_UNAVAILABLE - the server was unable to accept the connection
   4 : MQTT_CONNECT_BAD_CREDENTIALS - the username / password were rejected
   5 : MQTT_CONNECT_UNAUTHORIZED - the client was not authorized to connect
*/


//    Serial.print ("TimeInMins is:");
//    Serial.println (TimeInMins);
//    char valueStr [5];
//    String str = (String)TimeInMins;
//    str.toCharArray(valueStr, 5);
//    Serial.print("Publish Status:");
//    Serial.println (client.publish(USERNAME PREAMBLE TOPIC, valueStr));
//    PrevTimeInMins = TimeInMins;
//    delay(500);
