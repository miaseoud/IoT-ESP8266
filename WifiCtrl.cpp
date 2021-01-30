    
/***********************************************************************************************************************************/
/*-------------------------------------------------------WiFi SSID & Password----------------------------------------------------*/
/***********************************************************************************************************************************/
#include <WifiCtrl.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

enum wirelessState wifiState;

char ssid[] = "";           //   network SSID
char pass[] = "";        //   network passord

bool bWifiMode;
/***********************************************************************************************************************************/
/*-------------------------------------------------------Access Point Settings----------------------------------------------------*/
/***********************************************************************************************************************************/
const char *ssidap = "ESP32 AccessPoint";
const char *passwordap = "anypassword";
IPAddress  apIP (192, 168, 0, 200);
/*******************************************************************************************************************************/



boolean bConnectWiFi (void)
{
  Serial.println(" ");
  Serial.print("Connecting to Wi-Fi ");
  WiFi.begin(ssid, pass);
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
    return 1;
  }
  else return 0;
}

void vidStartMDns(void)
{
  
 if (!MDNS.begin("esp32"))
  {
        Serial.println("Error setting up MDNS responder!");
       // while(1) {
         //   delay(1000);
        //}
    }
   // MDNS.addService("http", "tcp", 80);
   else
   {
     Serial.println("mDNS responder started");
   }
   MDNS.addService("http", "tcp", 80);
}
    
