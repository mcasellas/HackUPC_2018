#include <WiFi.h>
 
const char* ssid = "Vermell";
const char* password =  "zampapenes";
 
const uint16_t port = 80;
const char * host = "192.168.43.87";
 
void setup()
{
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
    client.println("Hello from ESP32!");
 
    Serial.println("Disconnecting...");
    client.stop();
 
    delay(10000);
}
