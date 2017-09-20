  /*************************************************************************************/
  /*---------------------------------- Called on "ON" ---------------------------------*/
  /**************************************************************************************/
void handleOn() {
  digitalWrite(led, 1);
  server.send(200, "text/html", form);
}
  /*************************************************************************************/
  /*---------------------------------- Called on "OFF"  ---------------------------------*/
  /**************************************************************************************/
void handleOff() {
  digitalWrite(led, 0);
  server.send(200, "text/html", form);
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
  int alarmint  = server.arg("alarm").toInt();
  Serial.print("Alarm Set @ ");
  Serial.print(alarmint);
  alarmmins = (alarmint / 100) * 60 + alarmint % 100;
  Serial.print("      Alarm in minutes=");
  Serial.println(alarmmins);
}