#include <HTTPClient.h>
#include "cJSON.h"
void GetRestStart(void) /* https://github.com/DaveGamble/cJSON#parsing-json */
{
  WiFiClient client;
  HTTPClient http;
  //Serial.print("[HTTP] begin...\n");
  if (http.begin("http://api.openweathermap.org/data/2.5/weather?q=alexandria,eg&units=metric&APPID="))
  {
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0)
    {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        const char * payloadChar = payload.c_str();
        //Serial.println(payloadChar);
        const cJSON *mainObjects = NULL;
        cJSON *monitor_json = cJSON_Parse(payloadChar);

        const cJSON *main = cJSON_GetObjectItemCaseSensitive(monitor_json, "main");
        cJSON *temperature = cJSON_GetObjectItemCaseSensitive(main , "temp");
        Serial.print("Weather in Alexandria is ");
        Serial.print(temperature->valuedouble );
        Serial.println("°C");
        cJSON_Delete(monitor_json);
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else
  {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}
        /*
          const cJSON *id = cJSON_GetObjectItemCaseSensitive(monitor_json, "id");
                   Serial.print("ID is ");
           Serial.println(id->valuedouble );

           const cJSON *main = cJSON_GetObjectItemCaseSensitive(monitor_json, "main");
          cJSON_ArrayForEach(mainObjects, main )
          {
           cJSON *temperature = cJSON_GetObjectItemCaseSensitive(mainObjects , "temp");
           Serial.print("Tempaerature is ");
           Serial.println(temperature->valuedouble );
          }
        */

