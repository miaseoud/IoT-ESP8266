#include "mainHTML.h"
  

ESP8266WebServer server(80);
void vidWebServerInit (void)
{
  server.on("/", []() {

  server.send(200, "text/html", form);
});
server.on("/ON",    handleOn);
server.on("/OFF",   handleOff);
server.on("/alarm", handleAlarm);
server.on("/cancel", handleCancel);
/*start listening for HTTP requests*/
server.begin();
Serial.println("HTTP webserver started");

}
