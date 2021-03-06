    
/***********************************************************************************************************************************/
/*-------------------------------------------------------WiFi SSID & Password----------------------------------------------------*/
/***********************************************************************************************************************************/
char ssid[] = "Ray-Ban 2";           //   network SSID
char pass[] = "";        //   network passord
/***********************************************************************************************************************************/
/*-------------------------------------------------------Access Point Settings----------------------------------------------------*/
/***********************************************************************************************************************************/
const char *ssidap = "ESP AP";
const char *passwordap = "anypassword";
IPAddress  apIP (192, 168, 0, 200);
/*******************************************************************************************************************************/

void vidStartAcessPoint (void)
{
    delay(1000);
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssidap, passwordap);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("");
    Serial.println("Not connected to WiFI");
    Serial.print("AP IP address: ");
    Serial.println(myIP);
}

boolean bConnectWiFi (void)
{
  Serial.println(" ");
  Serial.print("Connecting to Wi-Fi ");
  WiFi.begin(ssid, pass);
  /* ---- Wait for connection to establish ----*/
  for (int tries = 0; (WiFi.status() != WL_CONNECTED) && tries < 20; tries++) {
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
  if (!MDNS.begin("esp8266")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  else
  {
    Serial.println("mDNS responder started");
    
  }
}
