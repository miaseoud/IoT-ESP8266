#ifndef MAINHTML_H
#define MAINHTML_H
//html page
boolean bConnectWiFi (void);
void vidNtpInit (void);
void vidStartAcessPoint (void);
void vidWebServerInit (void);
void vidMqttInit (void);
int NtpRequestTime (void);
void vidMqttReconnect(void);
void callback(char* topic, byte * data, unsigned int length);
unsigned long sendNTPpacket(IPAddress& address);

String form = "<HEAD>"
              "<TITLE>Basic HTML Sample Page</TITLE>"
              "<style>"
              "body"
              "{"
               "background: rgb(2,0,36);"
               "background: linear-gradient(90deg, rgba(2,0,36,1) 0%, rgba(68,116,126,0.12088585434173671) 32%);"
              "}"
              "</style>"
              "</HEAD>"
              "<CENTER>"
              //"<BODY BGCOLOR=Yellow>"
              "<br><br><br><br>"
              "<H1>Wi-Fi Controller</H1>"
              "<IMG SRC='http://thewindowsclub.thewindowsclubco.netdna-cdn.com/wp-content/uploads/2014/02/Delete-Wi-Fi-Network-Profiles-W8.1-1.png'>"
              "<form action='/ON'><input type='submit' value='Turn On'></form>"
              "<form action='/OFF'><input type='submit' value='Turn Off'></form>"
              "<form action='/alarm'><p>Alarm <input type='text' name='alarmHour' size=1>:<input type='text' name='alarmMint' size=1><input type='submit' value='Set'></form>"
              "<form action='/cancel'><input type='submit' value='Cancel Alarm'></form>"
              "</CENTER>"
              "<center>"
              "<br>"
              "<H5>Copyright 2020, by <A HREF='test'>Mahmoud Aboul-Seoud</A></H5>"
              ;
#endif
