#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "test";
const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "you are connect to esp8266");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Configuring access point…");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.printf("AP IP address: "); Serial.println(myIP);

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {server.handleClient();}