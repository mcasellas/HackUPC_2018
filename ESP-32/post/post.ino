#include <WiFi.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"

const char* ssid     = "HACKUPC2018";
const char* password = "BIENE2018";

void setup() {
      Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println("Hello, i'm pipo");
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

char json[2] = "1";

void loop() {
       if(WiFi.status() == WL_CONNECTED)
       {
          HTTPClient http;
          //10.4.230.75
          http.begin("http://jsonplaceholder.typicode.com/posts");
          http.addHeader("Content-Type", "text,plain");
          int httpCode = http.POST(json);
          Serial.println(httpCode);
          if(httpCode > 0){
            String res = http.getString();
            Serial.println(res);
          }
          else{
            Serial.println("Error");
          }
          http.end();
       }
}
