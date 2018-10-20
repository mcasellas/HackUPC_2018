#include <WiFi.h>
 
const char* ssid = "Vermell";
const char* password =  "zampapenes";
 
const uint16_t port = 80;
const char * host;

char ips[8][16];

void error(char* msg)
{
  Serial.println(msg);
}

int my_atoi(char c[2])
{
  c = c-48
  return int(c);
}

void discover()
{
  //Recive ip from other ESP32
  char l[2];
  l[1]= client.read();
  l[0] = client.read();
  int max = my_atoi(l);  
  char ip[max];
  char c;
  for(int i = 1; i < max; ++i)
  {
    ip[i] = client.read();
  }
  if(client.read() != '*')
  {
    error("Error on discover Tx");
  }
}
 
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

  discover();
 
}
 
void loop()
{
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
      Serial.println("Client connected");
      while (client.available()>0) {
        char c = client.read();
        client.write(c);
        if(c == d) discover();
        else if()
        Serial.println(c);
      }
 
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
  }
}
