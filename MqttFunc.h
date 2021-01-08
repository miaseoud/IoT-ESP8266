
#ifndef MqttFunc_H
#define MqttFunc_H

void vidMqttConnect();
void callback(char* topic, unsigned char * data, unsigned int length);
void vidMqttInit (void);

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

#endif
