/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"

const char* ssid     = "HACKUPC2018";
const char* password = "BIENE2018";

const char* host = "http://jsonplaceholder.typicode.com/comments?id=10";

void setup()
{

    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println("Hello, i'm not pipo");
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

int value = 0;

void loop()
{
     if(WiFi.status() == WL_CONNECTED)
     {
        HTTPClient http;
        http.begin("http://jsonplaceholder.typicode.com/comments?id=10");
        int httpCode = http.GET(); 
        if(httpCode > 0)
        {
            String payload = http.getString();
            char json[payload.length()];
            for(int i = 0; i < payload.length(); ++i){
              json[i] = payload[i];
            }
            Serial.println("id: ");
            StaticJsonBuffer<200> jsonBuffer;
            JsonObject& root = jsonBuffer.parseObject(json);
            if(!root.success()) {
              Serial.println("Puto error");
              delay(5000);
              return;
            }
            Serial.println(root["email"].as<char*>());
            
        }
        else
        {
          Serial.println("Error");
        }
     }
     delay(100000);
}

