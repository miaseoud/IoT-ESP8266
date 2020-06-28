#include "mainHTML.h"
  
  /*************************************************************************************/
  /*---------------------------------- Called on "ON" ---------------------------------*/
  /**************************************************************************************/
void handleOn() {

  server.send(200, "text/html", form);
    Serial.print("Publish Status:");
    Serial.println (client.publish(USERNAME PREAMBLE ON_OFF_TOPIC, "ON"));

}
  /*************************************************************************************/
  /*---------------------------------- Called on "OFF"  ---------------------------------*/
  /**************************************************************************************/
void handleOff() {

  server.send(200, "text/html", form);
      Serial.print("Publish Status:");
    Serial.println (client.publish(USERNAME PREAMBLE ON_OFF_TOPIC, "OFF"));
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
