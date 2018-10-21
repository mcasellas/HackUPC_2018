
#include <WiFi.h>
#include <WiFiMulti.h>
#include "DHT.h"

int sensorLlum = 34;  
int sensorPluja = 35; 

WiFiMulti WiFiMulti;

const char* ssid     = "HACKUPC2018"; // Your SSID (Name of your WiFi)
const char* password = "BIENE2018"; //Your Wifi password

const char* host = "api.thingspeak.com";
String api_key = "1CP66ORKYHVQB48C"; // Your API Key provied by thingspeak

#define DHTPIN 15
#define DHTTYPE DHT11



float h = 0;
float t = 0;

int sensorLlumValor = 0;

int sensorPlujaValor = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
  Connect_to_Wifi();

}

void loop() {

  
  sensorLlumValor = analogRead(sensorLlum);

  sensorPlujaValor = analogRead(sensorPluja);
 
  h = dht.readHumidity();

  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error DHT");
    return;
  }


  Serial.print("llum = ");
  Serial.print(sensorLlumValor);
  Serial.print("\t pluja = ");
  Serial.print(sensorPlujaValor);

  Serial.print("\t temperatura = ");
  Serial.print(t);

  Serial.print("\t humitat = ");
  Serial.println(h);

  
  Send_Data();
  delay(2000);
 

}

void Connect_to_Wifi()
{

  // We start by connecting to a WiFi network
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void Send_Data()
{

  // map the moist to 0 and 100% for a nice overview in thingspeak.
  
  //value = constrain(value,0,5000);
  //value = map(value,0,5000,100,0);

  Serial.println("Prepare to send data");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(t);
    data_to_send += "&field2=";
    data_to_send += String(h);
    data_to_send += "&field3=";
    data_to_send += String(sensorLlumValor);
    data_to_send += "&field4=";
    data_to_send += String(sensorPlujaValor);
    data_to_send += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);
    Serial.println("Done");

    delay(1000);
  }

  client.stop();

}
