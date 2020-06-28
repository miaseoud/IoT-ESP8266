
#include <PubSubClient.h> /*https://pubsubclient.knolleary.net/api#state*/
/*--------Connect-------*/
#define SERVER          "io.adafruit.com"
#define SERVERPORT      1883
#define MQTT_USERNAME   "miaseoud"
#define MQTT_KEY        ""
/*--------Publish & Subscribe -------*/
#define USERNAME          "miaseoud/"
#define PREAMBLE          "feeds/"
#define ON_OFF_TOPIC         "OnOff"
#define TOPIC             "TimeTopic"

WiFiClient WiFi_Client;//Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().
//Creates an uninitialised client instance(MQTT object).
//Before it can be used, it must be configured with the property setters:
PubSubClient client(WiFi_Client);//Constructor
extern TimeCheck NonBlock5Sec;

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


void vidMqttInit (void)
{
  client.setServer(SERVER, SERVERPORT);
  //client.subscribe(USERNAME PREAMBLE ON_OFF_TOPIC, 1);
  client.setCallback(callback);
}

void vidMqttConnect()
{
  if (!client.connected())
  {
    if (NonBlock5Sec.vidIsItTime())
    {
      Serial.print("Attempting MQTT connection . . . ");
      // Attempt to connect
      if (client.connect("", MQTT_USERNAME, MQTT_KEY)) {
        Serial.println("Connected");
        // ... and resubscribe
        client.subscribe(USERNAME PREAMBLE ON_OFF_TOPIC, 1);
      }
      else
      {
        Serial.println("Failed");
      }
    }
  }
else
{
  client.loop();
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

