#include <WiFiUdp.h>
#include "NTP.h"
WiFiUDP udp;
unsigned int localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
 // NTP time stamp is in the first 48 bytes of the message

int alarmmins = 1000000;
int mins;
TimeCheck NonBlock20Sec(20000);
TimeCheck NonBlock5Sec(5000);
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
  delay(500);

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

    int hours=((epoch  % 86400L) / 3600);
    int mins = ((epoch  % 3600) / 60);
    int seconds= (epoch % 60);
    Serial.print("Time is ");
    Serial.print(hours);
    Serial.print(':');
    if ( mins < 10 )
      Serial.print('0');
    Serial.print(mins); 
    Serial.print(':');
    if ( seconds  < 10 ) // In the first 10 seconds of each minute, we'll want a leading '0'    
      Serial.print('0');
    Serial.println(seconds);
    return hours*60 + mins;
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
