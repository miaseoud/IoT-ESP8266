#include <WiFiUdp.h>
#include "NTP.h"
int alarmmins = 1000000;
int mins;
TimeCheck NtpRequester(30000);
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
/**********************************************************************************************/
int NtpRequestTime (void)
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208985200UL;
    unsigned long epoch = secsSince1900 - seventyYears;

    Serial.print("Time is ");
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    int mins = ((epoch   % 86400L) / 3600) * 60;
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    mins = mins + ((epoch  % 3600) / 60);
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
    //Serial.print("Time in minutes=");
   // Serial.println(mins);
    return mins;
  }
}


void vidCheckAlarm (void)
{
    mins = NtpRequestTime();
    /*------------------------------------ Check ALARM ----------------------------------------------*/
    if (mins >= alarmmins) { //mins=minutes from 0:00 to current time
      Serial.println("Activate Alarm");//Alert set time is now
    }
  }

void vidNtpInit (void)
{
  Serial.println("Starting UDP for NTP requests");
  udp.begin(localPort);
  //Serial.print("Local port: ");
  //Serial.println(udp.localPort());
}


bool TimeCheck:: vidIsItTime (void)
{
  if ((millis() - previousMillis) > Interval)
  {
    //In order to not use request NTP continuisly
    previousMillis = millis();
    return 1;
  }
  else
  {
    return 0;
  }
}
