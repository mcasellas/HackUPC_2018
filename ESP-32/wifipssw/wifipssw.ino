#include <WiFi.h>
#include <DNSServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
WiFiServer server(80);

String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>Pipo's house</title></head><body>"
                      "<h1>PIPO's house</h1><br>"
                      "<script> funciton formToJson(form){"
                        "var form.pass = form.pass.value"
                        "var form.ssid = form.ssid.value"
                        "var jsonFormInfo = JSON.stringify({"
                          "pass: pass,"
                          "ssid: ssid"
                        "});"
                        "window.alert(jsonFormInfo),"
                      "</script>"
                      "<form onSubmit = 'event.preventDefault(); formToJson(this);'>"
                        "<input type = 'text' name = 'ssid'/><br>"
                        "<input type = 'text' name = 'pass'/><br>"
                        "<input type='submit' value='Submit'>"
                      "</form>";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("hackUVIC");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(responseHTML);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}
